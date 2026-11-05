package com.fexed.spacecadetpinball;

import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.DocumentsContract;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.EnumMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * Where the Full Tilt! data of each table comes from: the assets of an APK built with the data, or the files the player
 * imported from a copy of the original game (the data is copyrighted and is not part of the released app).
 */
final class TableFiles {
    private static final int SEARCH_DEPTH = 4; // the disc root holds WIN95/FULLTILT/CADET

    private TableFiles() {
    }

    /** The folder the imported files of a table are kept in. */
    static File importDir(Context context, Table table) {
        return new File(new File(context.getFilesDir(), "import"), table.id);
    }

    static boolean hasImported(Context context, Table table) {
        return new File(importDir(context, table), table.datFile).isFile();
    }

    /** Dragon's Keep has no steel ball of its own: its ball sprites come from Space Cadet's data. */
    static File cadetSource(Context context) {
        if (Table.CADET.isInstalled(context.getAssets())) return null;
        File imported = new File(importDir(context, Table.CADET), Table.CADET.datFile);
        return imported.isFile() ? imported : null;
    }

    static boolean isAvailable(Context context, Table table) {
        if (table.isInstalled(context.getAssets())) return true;
        if (!hasImported(context, table)) return false;
        return table != Table.DRAGON || Table.CADET.isInstalled(context.getAssets()) || cadetSource(context) != null;
    }

    /** The outcome of an import: the tables that were found and copied. */
    static final class Result {
        final List<Table> imported = new ArrayList<>();
        final List<Table> missing = new ArrayList<>();
    }

    /**
     * Looks for the tables below the folder the player picked (the folder of the game, or the folder of a single table)
     * and copies the files each one needs into the app. Call from a background thread.
     */
    static Result importTree(Context context, Uri tree) throws IOException {
        ContentResolver resolver = context.getContentResolver();
        Map<Table, String> folders = new EnumMap<>(Table.class);
        scan(resolver, tree, DocumentsContract.getTreeDocumentId(tree), 0, folders);

        Result result = new Result();
        for (Table table : Table.values()) {
            String folder = folders.get(table);
            if (folder == null) {
                result.missing.add(table);
                continue;
            }
            File dir = importDir(context, table);
            deleteRecursive(dir);
            if (!dir.mkdirs() && !dir.isDirectory()) throw new IOException("Unable to create " + dir);
            copyTable(resolver, tree, folder, table, dir);
            // the work folder is rebuilt from the imported files the next time the table starts
            deleteRecursive(new File(context.getFilesDir(), table.id));
            if (table == Table.CADET) deleteRecursive(new File(context.getFilesDir(), Table.DRAGON.id));
            result.imported.add(table);
        }
        return result;
    }

    /** Finds the folder of each table by the data file it holds, whatever the folder is called. */
    private static void scan(ContentResolver resolver, Uri tree, String folder, int depth, Map<Table, String> found) {
        List<Doc> children = children(resolver, tree, folder);
        boolean isTableFolder = false;
        for (Table table : Table.values()) {
            for (Doc child : children) {
                if (!child.directory && child.name.equalsIgnoreCase(table.datFile)) {
                    if (!found.containsKey(table)) found.put(table, folder);
                    isTableFolder = true;
                }
            }
        }
        if (isTableFolder || depth >= SEARCH_DEPTH) return;
        for (Doc child : children) {
            if (child.directory) scan(resolver, tree, child.id, depth + 1, found);
        }
    }

    /** The data file, the icon and the sound files of a table; the original uses upper case names. */
    private static void copyTable(ContentResolver resolver, Uri tree, String folder, Table table, File dir) throws IOException {
        boolean icon = false;
        boolean sounds = false;
        List<Doc> children = children(resolver, tree, folder);
        for (Doc child : children) {
            String lower = child.name.toLowerCase(Locale.ROOT);
            if (child.directory) {
                if (lower.equals("sound")) {
                    sounds = true;
                    for (Doc sound : children(resolver, tree, child.id)) {
                        if (!sound.directory) copy(resolver, tree, sound.id, new File(dir, sound.name.toUpperCase(Locale.ROOT)));
                    }
                }
            } else if (lower.equals(table.datFile.toLowerCase(Locale.ROOT))) {
                copy(resolver, tree, child.id, new File(dir, table.datFile));
            } else if (lower.endsWith(".bmp") && !icon) {
                icon = true;
                copy(resolver, tree, child.id, new File(dir, "icon.bmp"));
            }
        }
        if (!sounds) {
            // some copies keep the sound files next to the data file
            for (Doc child : children) {
                String lower = child.name.toLowerCase(Locale.ROOT);
                if (!child.directory && (lower.endsWith(".wav") || lower.endsWith(".mds") || lower.endsWith(".mid"))) {
                    copy(resolver, tree, child.id, new File(dir, child.name.toUpperCase(Locale.ROOT)));
                }
            }
        }
    }

    private static final class Doc {
        final String id;
        final String name;
        final boolean directory;

        Doc(String id, String name, boolean directory) {
            this.id = id;
            this.name = name;
            this.directory = directory;
        }
    }

    private static List<Doc> children(ContentResolver resolver, Uri tree, String folder) {
        List<Doc> list = new ArrayList<>();
        Uri uri = DocumentsContract.buildChildDocumentsUriUsingTree(tree, folder);
        String[] columns = {DocumentsContract.Document.COLUMN_DOCUMENT_ID, DocumentsContract.Document.COLUMN_DISPLAY_NAME,
                DocumentsContract.Document.COLUMN_MIME_TYPE};
        try (Cursor cursor = resolver.query(uri, columns, null, null, null)) {
            while (cursor != null && cursor.moveToNext()) {
                boolean directory = DocumentsContract.Document.MIME_TYPE_DIR.equals(cursor.getString(2));
                list.add(new Doc(cursor.getString(0), cursor.getString(1), directory));
            }
        } catch (RuntimeException e) {
            // an unreadable folder counts as empty
        }
        return list;
    }

    private static void copy(ContentResolver resolver, Uri tree, String document, File target) throws IOException {
        Uri uri = DocumentsContract.buildDocumentUriUsingTree(tree, document);
        try (InputStream in = resolver.openInputStream(uri); OutputStream out = new FileOutputStream(target)) {
            if (in == null) throw new IOException("Unable to read " + target.getName());
            byte[] buffer = new byte[16384];
            int len;
            while ((len = in.read(buffer)) != -1) out.write(buffer, 0, len);
        }
    }

    static void deleteRecursive(File file) {
        File[] children = file.listFiles();
        if (children != null) for (File child : children) deleteRecursive(child);
        file.delete();
    }
}
