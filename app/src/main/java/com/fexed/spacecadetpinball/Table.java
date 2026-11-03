package com.fexed.spacecadetpinball;

import android.content.res.AssetManager;

import java.io.IOException;

/** The tables the app can run. Classic ships in the asset root, Full Tilt tables in their own asset folder. */
public enum Table {
    CLASSIC("classic", "Space Cadet (3D Pinball)", "PINBALL.DAT", false, true),
    CADET("cadet", "Space Cadet", "CADET.DAT", true, true),
    DRAGON("dragon", "Dragon's Keep", "DRAGON.DAT", true, false),
    PIRATES("pirates", "Skulduggery", "PIRATES.DAT", true, false);

    public final String id;
    public final String title;
    public final String datFile;
    public final boolean fullTilt;
    /** False while the engine has no rules for this table. */
    public final boolean playable;

    Table(String id, String title, String datFile, boolean fullTilt, boolean playable) {
        this.id = id;
        this.title = title;
        this.datFile = datFile;
        this.fullTilt = fullTilt;
        this.playable = playable;
    }

    /** Asset folder holding this table's files; null for the classic table whose files sit in the asset root. */
    public String assetDir() {
        return fullTilt ? id : null;
    }

    public boolean isInstalled(AssetManager assets) {
        try {
            if (!fullTilt) return true;
            String[] files = assets.list(id);
            return files != null && files.length > 0;
        } catch (IOException e) {
            return false;
        }
    }

    public static Table byId(String id) {
        for (Table t : values()) if (t.id.equals(id)) return t;
        return CLASSIC;
    }
}
