package com.fexed.spacecadetpinball;

import android.content.res.AssetManager;

import java.io.IOException;

/** The Full Tilt! tables the app can run, each with its data in its own asset folder. */
public enum Table {
    CADET("cadet", "Space Cadet", "CADET.DAT", true, true),
    DRAGON("dragon", "Dragon's Keep", "DRAGON.DAT", true, false),
    PIRATES("pirates", "Skulduggery", "PIRATES.DAT", true, false);

    public final String id;
    public final String title;
    public final String datFile;
    public final boolean fullTilt;
    /** False while the engine has no scoring rules for this table: it only plays as a bare table. */
    public final boolean hasRules;

    Table(String id, String title, String datFile, boolean fullTilt, boolean hasRules) {
        this.id = id;
        this.title = title;
        this.datFile = datFile;
        this.fullTilt = fullTilt;
        this.hasRules = hasRules;
    }

    /** Asset folder holding this table's files. */
    public String assetDir() {
        return id;
    }

    public boolean isInstalled(AssetManager assets) {
        try {
            String[] files = assets.list(id);
            return files != null && files.length > 0;
        } catch (IOException e) {
            return false;
        }
    }

    public static Table byId(String id) {
        for (Table t : values()) if (t.id.equals(id)) return t;
        return CADET;
    }
}
