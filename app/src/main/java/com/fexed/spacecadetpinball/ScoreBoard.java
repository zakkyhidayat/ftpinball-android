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

    static final class Entry {
        final String name;
        final int score;
        final long date;

        Entry(String name, int score, long date) {
            this.name = name;
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
                entries.add(new Entry(o.getString("name"), o.getInt("score"), o.getLong("date")));
            }
        } catch (JSONException ignored) {
        }
        return entries;
    }

    /** Adds a score and returns its rank (1-based), or 0 if it did not make the top 10. */
    static int add(Context context, String tableId, String name, int score, long date) {
        List<Entry> entries = get(context, tableId);
        int index = 0;
        while (index < entries.size() && entries.get(index).score >= score) index++;
        if (index >= MAX_ENTRIES) return 0;
        entries.add(index, new Entry(name, score, date));
        while (entries.size() > MAX_ENTRIES) entries.remove(entries.size() - 1);

        JSONArray array = new JSONArray();
        try {
            for (Entry e : entries) {
                array.put(new JSONObject().put("name", e.name).put("score", e.score).put("date", e.date));
            }
        } catch (JSONException e) {
            return 0;
        }
        prefs(context).edit().putString(tableId, array.toString()).apply();
        return index + 1;
    }
}
