package com.fexed.spacecadetpinball;

import android.content.Context;
import android.content.SharedPreferences;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

/** Local top 10 high scores, one list per table. */
final class ScoreBoard {
    static final int MAX_ENTRIES = 10;
    static final int MAX_RECENT = 10;

    static final class Entry {
        final int score;
        final long date;

        Entry(int score, long date) {
            this.score = score;
            this.date = date;
        }
    }

    private ScoreBoard() {
    }

    private static SharedPreferences prefs(Context context) {
        return context.getSharedPreferences("com.fexed.spacecadetpinball.scores", Context.MODE_PRIVATE);
    }

    static List<Entry> get(Context context, String tableId) {
        List<Entry> entries = new ArrayList<>();
        try {
            JSONArray array = new JSONArray(prefs(context).getString(tableId, "[]"));
            for (int i = 0; i < array.length(); i++) {
                JSONObject o = array.getJSONObject(i);
                entries.add(new Entry(o.getInt("score"), o.getLong("date")));
            }
        } catch (JSONException ignored) {
        }
        return entries;
    }

    private static String recentKey(String tableId) {
        return tableId + "_recent";
    }

    /** Formats a score with a comma between every three digits. */
    static String format(int score) {
        return String.format(java.util.Locale.US, "%,d", score);
    }

    /** Puts a comma between every three digits of each long number in a message. */
    static String commas(String text) {
        java.util.regex.Matcher m = java.util.regex.Pattern.compile("(?<![\\d.,])\\d{4,}(?![\\d.,])").matcher(text);
        StringBuffer out = new StringBuffer();
        while (m.find()) {
            try {
                m.appendReplacement(out, format(Integer.parseInt(m.group())));
            } catch (NumberFormatException e) {
                m.appendReplacement(out, m.group());
            }
        }
        m.appendTail(out);
        return out.toString();
    }

    /** The latest games, newest first. */
    static List<Entry> getRecent(Context context, String tableId) {
        List<Entry> entries = new ArrayList<>();
        try {
            JSONArray array = new JSONArray(prefs(context).getString(recentKey(tableId), "[]"));
            for (int i = 0; i < array.length(); i++) {
                JSONObject o = array.getJSONObject(i);
                entries.add(new Entry(o.getInt("score"), o.getLong("date")));
            }
        } catch (JSONException ignored) {
        }
        return entries;
    }

    /** Games played and the sum of their scores, for the average. */
    static long[] getStats(Context context, String tableId) {
        return new long[]{prefs(context).getLong(tableId + "_games", 0), prefs(context).getLong(tableId + "_total", 0)};
    }

    private static void addRecent(Context context, String tableId, int score, long date) {
        long[] stats = getStats(context, tableId);
        prefs(context).edit().putLong(tableId + "_games", stats[0] + 1).putLong(tableId + "_total", stats[1] + score).apply();
        List<Entry> entries = getRecent(context, tableId);
        entries.add(0, new Entry(score, date));
        while (entries.size() > MAX_RECENT) entries.remove(entries.size() - 1);
        JSONArray array = new JSONArray();
        try {
            for (Entry e : entries) array.put(new JSONObject().put("score", e.score).put("date", e.date));
        } catch (JSONException e) {
            return;
        }
        prefs(context).edit().putString(recentKey(tableId), array.toString()).apply();
    }

    /** Adds a score and returns its rank (1-based), or 0 if it did not make the top 10. */
    static int add(Context context, String tableId, int score, long date) {
        addRecent(context, tableId, score, date);
        List<Entry> entries = get(context, tableId);
        int index = 0;
        while (index < entries.size() && entries.get(index).score >= score) index++;
        if (index >= MAX_ENTRIES) return 0;
        entries.add(index, new Entry(score, date));
        while (entries.size() > MAX_ENTRIES) entries.remove(entries.size() - 1);

        JSONArray array = new JSONArray();
        try {
            for (Entry e : entries) {
                array.put(new JSONObject().put("score", e.score).put("date", e.date));
            }
        } catch (JSONException e) {
            return 0;
        }
        prefs(context).edit().putString(tableId, array.toString()).apply();
        return index + 1;
    }
}
