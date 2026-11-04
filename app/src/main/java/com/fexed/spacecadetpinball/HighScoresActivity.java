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
                    ? getString(R.string.gameover_rank, score, highlightRank)
                    : getString(R.string.gameover_score, score));
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

    private void buildList() {
        LinearLayout list = findViewById(R.id.hs_list);
        list.removeAllViews();
        ((TextView) findViewById(R.id.hs_table)).setText(table.title);
        List<ScoreBoard.Entry> entries = ScoreBoard.get(this, table.id);
        findViewById(R.id.hs_empty).setVisibility(entries.isEmpty() ? View.VISIBLE : View.GONE);
        DateFormat dates = DateFormat.getDateInstance(DateFormat.MEDIUM);
        LayoutInflater inflater = LayoutInflater.from(this);
        for (int i = 0; i < entries.size(); i++) {
            ScoreBoard.Entry e = entries.get(i);
            View row = inflater.inflate(R.layout.item_score, list, false);
            ((TextView) row.findViewById(R.id.sc_rank)).setText(String.valueOf(i + 1));
            ((TextView) row.findViewById(R.id.sc_name)).setText(e.name);
            ((TextView) row.findViewById(R.id.sc_date)).setText(dates.format(new Date(e.date)));
            TextView score = row.findViewById(R.id.sc_score);
            score.setText(String.valueOf(e.score));
            if (i + 1 == highlightRank && getIntent().getBooleanExtra(EXTRA_GAME_OVER, false)) {
                row.setBackgroundResource(R.drawable.bg_card);
                score.setTypeface(null, Typeface.BOLD);
            }
            list.addView(row);
        }
    }
}
