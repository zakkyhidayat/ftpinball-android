package com.fexed.spacecadetpinball;

import android.content.res.AssetManager;

import java.io.IOException;

/** The Full Tilt! tables the app can run, each with its data in its own asset folder. */
public enum Table {
    CADET("cadet", "Space Cadet", "CADET.DAT", true, true, 0xFF8F8FF2),
    DRAGON("dragon", "Dragon's Keep", "DRAGON.DAT", true, false, 0xFFD0303F),
    PIRATES("pirates", "Skulduggery", "PIRATES.DAT", true, false, 0xFFE0392B);

    public final String id;
    public final String title;
    public final String datFile;
    public final boolean fullTilt;
    /** False while the engine has no scoring rules for this table: it only plays as a bare table. */
    public final boolean hasRules;
    /** Color of the table's own score and message text in the original game (taken from its sidebar). */
    public final int accent;

    Table(String id, String title, String datFile, boolean fullTilt, boolean hasRules, int accent) {
        this.id = id;
        this.title = title;
        this.datFile = datFile;
        this.fullTilt = fullTilt;
        this.hasRules = hasRules;
        this.accent = accent;
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
