package com.fexed.spacecadetpinball;

import android.Manifest;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.provider.DocumentsContract;
import android.system.ErrnoException;
import android.system.Os;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;

/**
 * Where the Full Tilt! data of each table comes from: the assets of an APK built with the data, or the folder of the
 * player's own copy of the game, which stays where it is (the data is copyrighted and is not part of the released app).
 * The game process finds the files of an external table through links in the app's own folder.
 */
final class TableFiles {
    private static final String PREFS = "com.fexed.spacecadetpinball.files";
    private static final String KEY_SOURCE = "source_";
    private static final int SEARCH_DEPTH = 4; // the disc root holds WIN95/FULLTILT/CADET

    private TableFiles() {
    }

    /** Whether the app may read the folders of the player's game: "all files access", or the storage permission. */
    static boolean hasAccess(Context context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) return Environment.isExternalStorageManager();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            return context.checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED;
        }
        return true;
    }

    private static SharedPreferences prefs(Context context) {
        return context.getSharedPreferences(PREFS, Context.MODE_PRIVATE);
    }

    /** The folder of the player's copy that holds this table, or null. */
    static File source(Context context, Table table) {
        String path = prefs(context).getString(KEY_SOURCE + table.id, null);
        if (path == null) return null;
        File dir = new File(path);
        return child(dir, table.datFile) != null ? dir : null;
    }

    /** The icon file of the player's copy of a table, or null. */
    static File icon(Context context, Table table) {
        File source = source(context, table);
        File[] children = source == null ? null : source.listFiles();
        if (children == null) return null;
        Arrays.sort(children);
        for (File file : children) {
            if (file.isFile() && file.getName().toLowerCase(Locale.ROOT).endsWith(".bmp")) return file;
        }
        return null;
    }

    static boolean isAvailable(Context context, Table table) {
        if (table.isInstalled(context.getAssets())) return true;
        return hasAccess(context) && source(context, table) != null;
    }

    /** The folder a tree picked with the system folder picker stands for, or null when it is not on shared storage. */
    static File treeToPath(Uri tree) {
        String id = DocumentsContract.getTreeDocumentId(tree);
        int colon = id.indexOf(':');
        if (colon < 0) return null;
        String volume = id.substring(0, colon);
        String relative = id.substring(colon + 1);
        File base = "primary".equals(volume) ? Environment.getExternalStorageDirectory() : new File("/storage/" + volume);
        return relative.isEmpty() ? base : new File(base, relative);
    }

    /** The outcome of choosing a folder: the tables that were found there. */
    static final class Result {
        final List<Table> found = new ArrayList<>();
        final List<Table> missing = new ArrayList<>();
    }

    /** Looks for the tables below the folder the player chose (the game folder, the disc, or one table's folder). */
    static Result useFolder(Context context, File root) {
        java.util.Map<Table, File> folders = new java.util.EnumMap<>(Table.class);
        scan(root, 0, folders);
        Result result = new Result();
        SharedPreferences.Editor editor = prefs(context).edit();
        for (Table table : Table.values()) {
            File folder = folders.get(table);
            if (folder == null) {
                result.missing.add(table);
                continue;
            }
            editor.putString(KEY_SOURCE + table.id, folder.getAbsolutePath());
            // the table's own folder is rebuilt from the new location the next time it starts
            deleteRecursive(new File(context.getFilesDir(), table.id));
            result.found.add(table);
        }
        editor.apply();
        return result;
    }

    /** Finds the folder of each table by the data file it holds, whatever the folder is called. */
    private static void scan(File folder, int depth, java.util.Map<Table, File> found) {
        File[] children = folder.listFiles();
        if (children == null) return;
        boolean isTableFolder = false;
        for (Table table : Table.values()) {
            if (child(folder, table.datFile) != null) {
                if (!found.containsKey(table)) found.put(table, folder);
                isTableFolder = true;
            }
        }
        if (isTableFolder || depth >= SEARCH_DEPTH) return;
        Arrays.sort(children);
        for (File child : children) {
            if (child.isDirectory()) scan(child, depth + 1, found);
        }
    }

    /** The file of a folder with this name, ignoring case. */
    private static File child(File folder, String name) {
        File[] children = folder.listFiles();
        if (children == null) return null;
        for (File child : children) {
            if (child.isFile() && child.getName().equalsIgnoreCase(name)) return child;
        }
        return null;
    }

    /**
     * Links the data file, the icon and the sound and music files of an external table into the table's own folder, with
     * the upper case names of the original. The files themselves are not copied.
     */
    static void link(Context context, Table table, File dir) throws IOException {
        File source = source(context, table);
        if (source == null) throw new IOException("No folder for " + table.id);
        linkFile(child(source, table.datFile), new File(dir, table.datFile));
        File[] children = source.listFiles();
        if (children == null) return;
        boolean icon = false;
        boolean sounds = false;
        for (File file : children) {
            String lower = file.getName().toLowerCase(Locale.ROOT);
            if (file.isDirectory() && lower.equals("sound")) {
                sounds = true;
                File[] files = file.listFiles();
                if (files != null) {
                    for (File sound : files) {
                        if (sound.isFile()) linkFile(sound, new File(dir, sound.getName().toUpperCase(Locale.ROOT)));
                    }
                }
            } else if (file.isFile() && lower.endsWith(".bmp") && !icon) {
                icon = true;
                linkFile(file, new File(dir, "icon.bmp"));
            }
        }
        if (!sounds) {
            // some copies keep the sound files next to the data file
            for (File file : children) {
                String lower = file.getName().toLowerCase(Locale.ROOT);
                if (file.isFile() && (lower.endsWith(".wav") || lower.endsWith(".mds") || lower.endsWith(".mid"))) {
                    linkFile(file, new File(dir, file.getName().toUpperCase(Locale.ROOT)));
                }
            }
        }
    }

    private static void linkFile(File target, File link) throws IOException {
        if (target == null) throw new IOException("Missing file for " + link.getName());
        if (link.exists() || isLink(link)) link.delete();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            try {
                Os.symlink(target.getAbsolutePath(), link.getAbsolutePath());
                return;
            } catch (ErrnoException e) {
                // fall through to a copy
            }
        }
        try (InputStream in = new FileInputStream(target); OutputStream out = new FileOutputStream(link)) {
            byte[] buffer = new byte[16384];
            int len;
            while ((len = in.read(buffer)) != -1) out.write(buffer, 0, len);
        }
    }

    private static boolean isLink(File file) {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP) return false;
        try {
            Os.readlink(file.getAbsolutePath());
            return true;
        } catch (ErrnoException e) {
            return false;
        }
    }

    static void deleteRecursive(File file) {
        File[] children = isLink(file) ? null : file.listFiles();
        if (children != null) for (File child : children) deleteRecursive(child);
        file.delete();
    }
}
