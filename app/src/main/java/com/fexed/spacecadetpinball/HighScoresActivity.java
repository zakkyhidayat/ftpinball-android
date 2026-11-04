package com.fexed.spacecadetpinball;

import android.content.Context;
import android.graphics.Typeface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.text.DateFormat;
import java.util.Date;
import java.util.List;

/** Top 10 scores per table; also shown after a game with the new score highlighted. */
public class HighScoresActivity extends AppCompatActivity {
    public static final String EXTRA_TABLE = "table";
    public static final String EXTRA_SCORE = "score";
    public static final String EXTRA_RANK = "rank";
    public static final String EXTRA_GAME_OVER = "gameover";

    private Table table;
    private int highlightRank;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_highscores);
        if (getSupportActionBar() != null) getSupportActionBar().hide();

        table = Table.byId(getIntent().getStringExtra(EXTRA_TABLE));
        highlightRank = getIntent().getIntExtra(EXTRA_RANK, 0);
        boolean gameOver = getIntent().getBooleanExtra(EXTRA_GAME_OVER, false);

        TextView title = findViewById(R.id.hs_title);
        TextView subtitle = findViewById(R.id.hs_subtitle);
        Button primary = findViewById(R.id.hs_primary);
        Button close = findViewById(R.id.hs_close);

        if (gameOver) {
            int score = getIntent().getIntExtra(EXTRA_SCORE, 0);
            title.setText(R.string.gameover_title);
            subtitle.setVisibility(View.VISIBLE);
            subtitle.setText(highlightRank > 0
                    ? getString(R.string.gameover_rank, ScoreBoard.format(score), highlightRank)
                    : getString(R.string.gameover_score, ScoreBoard.format(score)));
            primary.setVisibility(View.VISIBLE);
            primary.setOnClickListener(v -> {
                setResult(RESULT_OK);
                finish();
            });
            close.setText(R.string.back_to_menu);
            close.setOnClickListener(v -> {
                setResult(RESULT_CANCELED);
                finish();
            });
        } else {
            title.setText(R.string.highscores_title);
            close.setText(R.string.close);
            close.setOnClickListener(v -> finish());
            buildTableChips();
        }
        buildList();
    }

    private void buildTableChips() {
        LinearLayout chips = findViewById(R.id.hs_chips);
        chips.setVisibility(View.VISIBLE);
        chips.removeAllViews();
        for (Table t : Table.values()) {
            if (!t.isInstalled(getAssets())) continue;
            Button chip = new Button(this, null, com.google.android.material.R.attr.materialButtonOutlinedStyle);
            chip.setText(t.title);
            chip.setAllCaps(false);
            chip.setAlpha(t == table ? 1f : 0.5f);
            chip.setOnClickListener(v -> {
                table = t;
                buildTableChips();
                buildList();
            });
            chips.addView(chip);
        }
    }

    private static final int SHOWN = 3;

    private void buildList() {
        ((TextView) findViewById(R.id.hs_table)).setText(table.title);
        List<ScoreBoard.Entry> top = ScoreBoard.get(this, table.id);
        List<ScoreBoard.Entry> recent = ScoreBoard.getRecent(this, table.id);
        boolean empty = top.isEmpty() && recent.isEmpty();
        long[] stats = ScoreBoard.getStats(this, table.id);
        TextView statsView = findViewById(R.id.hs_stats);
        statsView.setVisibility(stats[0] > 0 ? View.VISIBLE : View.GONE);
        if (stats[0] > 0) {
            int best = top.isEmpty() ? 0 : top.get(0).score;
            statsView.setText(getString(R.string.hs_stats, String.valueOf(stats[0]), ScoreBoard.format(best),
                    ScoreBoard.format((int) (stats[1] / stats[0]))));
        }
        findViewById(R.id.hs_empty).setVisibility(empty ? View.VISIBLE : View.GONE);
        findViewById(R.id.hs_top_header).setVisibility(empty ? View.GONE : View.VISIBLE);
        findViewById(R.id.hs_recent_header).setVisibility(recent.isEmpty() ? View.GONE : View.VISIBLE);
        boolean gameOver = getIntent().getBooleanExtra(EXTRA_GAME_OVER, false);
        fillList((LinearLayout) findViewById(R.id.hs_list), top, highlightRank > 0 && gameOver ? highlightRank : 0, true);
        // in the recent list the game just played is the first row
        fillList((LinearLayout) findViewById(R.id.hs_recent_list), recent, gameOver ? 1 : 0, false);
    }

    private void fillList(LinearLayout list, List<ScoreBoard.Entry> entries, int highlight, boolean ranked) {
        list.removeAllViews();
        DateFormat dates = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.SHORT);
        LayoutInflater inflater = LayoutInflater.from(this);
        for (int i = 0; i < Math.min(SHOWN, entries.size()); i++) {
            ScoreBoard.Entry e = entries.get(i);
            View row = inflater.inflate(R.layout.item_score, list, false);
            ((TextView) row.findViewById(R.id.sc_rank)).setText(ranked ? String.valueOf(i + 1) : "\u2022");
            ((TextView) row.findViewById(R.id.sc_date)).setText(dates.format(new Date(e.date)));
            TextView score = row.findViewById(R.id.sc_score);
            score.setText(ScoreBoard.format(e.score));
            if (i + 1 == highlight) {
                row.setBackgroundResource(R.drawable.bg_card);
                score.setTypeface(null, Typeface.BOLD);
            }
            list.addView(row);
        }
    }
}
