package com.fexed.spacecadetpinball;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.text.DateFormat;
import java.util.Date;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;
import androidx.appcompat.app.AppCompatActivity;

import java.io.IOException;
import java.io.InputStream;

/** Main menu: pick a table, open settings or the credits. */
public class MenuActivity extends AppCompatActivity {
    private static final String PREFS = "com.fexed.spacecadetpinball.menu";
    private static final String KEY_LAST_TABLE = "lasttable";
    private static final String KEY_PLAYED_AT = "playedat_";

    /** The folder picker for the player's copy of the game; the system gives the app access to the chosen folder only. */
    private final androidx.activity.result.ActivityResultLauncher<android.net.Uri> importLauncher =
            registerForActivityResult(new androidx.activity.result.contract.ActivityResultContracts.OpenDocumentTree(), uri -> {
                if (uri != null) importFiles(uri);
            });

    private void importFiles(android.net.Uri tree) {
        androidx.appcompat.app.AlertDialog progress = new MaterialAlertDialogBuilder(this)
                .setTitle(R.string.import_title)
                .setMessage(R.string.import_working)
                .setCancelable(false)
                .show();
        new Thread(() -> {
            TableFiles.Result result = null;
            try {
                result = TableFiles.importTree(getApplicationContext(), tree);
            } catch (IOException | RuntimeException e) {
                android.util.Log.e("Menu", "Import failed", e);
            }
            TableFiles.Result done = result;
            runOnUiThread(() -> {
                progress.dismiss();
                String message;
                if (done == null) {
                    message = getString(R.string.import_failed);
                } else if (done.imported.isEmpty()) {
                    message = getString(R.string.import_none);
                } else {
                    StringBuilder found = new StringBuilder();
                    for (Table t : done.imported) found.append(found.length() > 0 ? ", " : "").append(t.title);
                    message = getString(R.string.import_done, found);
                    if (!done.missing.isEmpty()) {
                        StringBuilder missing = new StringBuilder();
                        for (Table t : done.missing) missing.append(missing.length() > 0 ? ", " : "").append(t.title);
                        message += "\n" + getString(R.string.import_missing, missing);
                    }
                }
                new MaterialAlertDialogBuilder(this).setTitle(R.string.import_title).setMessage(message)
                        .setPositiveButton(android.R.string.ok, null).show();
                buildTableList();
            });
        }).start();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);
        if (getSupportActionBar() != null) getSupportActionBar().hide();

        findViewById(R.id.menusettings).setOnClickListener(v -> startActivity(new Intent(this, Settings.class)));
        findViewById(R.id.menuscores).setOnClickListener(v -> {
            Intent intent = new Intent(this, HighScoresActivity.class);
            intent.putExtra(HighScoresActivity.EXTRA_TABLE,
                    getSharedPreferences(PREFS, Context.MODE_PRIVATE).getString(KEY_LAST_TABLE, null));
            startActivity(intent);
        });
        findViewById(R.id.menuimport).setOnClickListener(v -> new MaterialAlertDialogBuilder(this)
                .setTitle(R.string.import_title)
                .setMessage(R.string.import_help)
                .setPositiveButton(R.string.import_choose, (d, w) -> importLauncher.launch(null))
                .setNegativeButton(android.R.string.cancel, null)
                .show());
        findViewById(R.id.menuabout).setOnClickListener(v -> new MaterialAlertDialogBuilder(this)
                .setTitle(R.string.about)
                .setMessage(R.string.menu_credits)
                .setPositiveButton(android.R.string.ok, null)
                .show());
    }

    @Override
    protected void onResume() {
        super.onResume();
        buildTableList();
    }

    private void buildTableList() {
        LinearLayout list = findViewById(R.id.tablelist);
        list.removeAllViews();
        SharedPreferences prefs = getSharedPreferences(PREFS, Context.MODE_PRIVATE);
        LayoutInflater inflater = LayoutInflater.from(this);

        for (Table table : Table.values()) {
            if (!TableFiles.isAvailable(this, table)) continue;
            View card = inflater.inflate(R.layout.item_table, list, false);
            ((TextView) card.findViewById(R.id.tabletitle)).setText(table.title);

            String desc = getString(table.hasRules ? R.string.table_fulltilt : R.string.table_norules);
            long playedAt = prefs.getLong(KEY_PLAYED_AT + table.id, 0);
            if (playedAt > 0) {
                desc += "\n" + getString(R.string.last_played) + ": "
                        + DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.SHORT).format(new Date(playedAt));
            }
            ((TextView) card.findViewById(R.id.tabledesc)).setText(desc);

            java.io.File sidebar = new java.io.File(getFilesDir(), table.id + "/" + ArtFiles.SIDEBAR);
            if (sidebar.exists()) {
                ((ImageView) card.findViewById(R.id.cardart)).setImageBitmap(BitmapFactory.decodeFile(sidebar.getAbsolutePath()));
            }

            ((TextView) card.findViewById(R.id.tabletitle)).setTextColor(table.accent);
            ImageView icon = card.findViewById(R.id.tableicon);
            icon.setClipToOutline(true);
            icon.setOutlineProvider(new android.view.ViewOutlineProvider() {
                @Override
                public void getOutline(View view, android.graphics.Outline outline) {
                    outline.setRoundRect(0, 0, view.getWidth(), view.getHeight(), 16 * getResources().getDisplayMetrics().density);
                }
            });
            Bitmap art = loadIcon(table);
            if (art != null) icon.setImageBitmap(art);
            else icon.setImageResource(R.drawable.star);

            card.setOnClickListener(v -> startTable(table));
            list.addView(card);
        }
        findViewById(R.id.nodata).setVisibility(list.getChildCount() == 0 ? View.VISIBLE : View.GONE);
    }

    /** Full Tilt tables ship a 120x120 icon next to their data. */
    private Bitmap loadIcon(Table table) {
        java.io.File imported = new java.io.File(TableFiles.importDir(this, table), "icon.bmp");
        if (!table.isInstalled(getAssets()) && imported.isFile()) return BitmapFactory.decodeFile(imported.getAbsolutePath());
        try (InputStream is = getAssets().open(table.assetDir() + "/icon.bmp")) {
            return BitmapFactory.decodeStream(is);
        } catch (IOException e) {
            return null;
        }
    }

    private void startTable(Table table) {
        getSharedPreferences(PREFS, Context.MODE_PRIVATE).edit().putString(KEY_LAST_TABLE, table.id)
                .putLong(KEY_PLAYED_AT + table.id, System.currentTimeMillis()).apply();
        Intent intent = new Intent(this, MainActivity.class);
        intent.putExtra(MainActivity.EXTRA_TABLE, table.id);
        startActivity(intent);
    }
}
