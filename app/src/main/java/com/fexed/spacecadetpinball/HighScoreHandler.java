package com.fexed.spacecadetpinball;

import android.util.Log;

class HighScoreHandler {
    /** Stores the score as the new local high score if it beats the old one and no cheats were used. */
    static boolean postHighScore(int score) {
        boolean updated = false;
        Log.d("RANKS", PrefsHelper.getCheatsUsed() + " " + score);

        if (!PrefsHelper.getCheatsUsed()) {
            int oldscore = PrefsHelper.getHighScore();
            if (score > oldscore) {
                PrefsHelper.setHighScore(score);
                updated = true;
            }
        }

        return updated;
    }
}
