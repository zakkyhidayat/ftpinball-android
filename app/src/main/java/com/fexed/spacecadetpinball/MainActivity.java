package com.fexed.spacecadetpinball;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.Typeface;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.Toast;

import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.core.content.res.ResourcesCompat;

import org.libsdl.app.SDLActivity;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.fexed.spacecadetpinball.databinding.ActivityMainBinding;
import com.google.firebase.analytics.FirebaseAnalytics;

public class MainActivity extends SDLActivity {
    private static final String TAG = "MainActivity";
    public static final String EXTRA_TABLE = "table";

    private ActivityMainBinding mBinding;
    private boolean leavingToMenu = false;
    private android.animation.ObjectAnimator plungerPulse;
    private boolean plungerHeld;
    private final Runnable plungerPowerUpdater = new Runnable() {
        @Override
        public void run() {
            if (!plungerHeld) return;
            mBinding.plunger.setPower(getPlungerPower());
            mBinding.plunger.postOnAnimation(this);
        }
    };
    // table height / width as rendered by the engine
    private static final float TABLE_ASPECT = 825f / 720f;
    private Table currentTable = Table.CADET;
    private static final int REQUEST_GAME_OVER = 1;
    private boolean isGameReady = false;
    private boolean isPlaying = true;

    private int ballCount = 0;
    private int remainingBalls = 0;

    private FirebaseAnalytics firebaseAnalytics;
    private int gamesInSession = 0;

    static private MediaPlayer player;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setVolumeControlStream(android.media.AudioManager.STREAM_MUSIC);
        Table table = Table.byId(getIntent().getStringExtra(EXTRA_TABLE));
        currentTable = table;
        File tableDir = prepareTableFiles(table);
        initNative(tableDir.getAbsolutePath() + "/", table.datFile, table.fullTilt);
        PrefsHelper.setPrefs(getSharedPreferences("com.fexed.spacecadetpinball", Context.MODE_PRIVATE));

        try {
            if (PrefsHelper.getMusic()) {
                player = new MediaPlayer();
                AssetFileDescriptor afd = getAssets().openFd("PINBALL.mp3");
                player.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
                player.prepare();
                player.setLooping(true);
                player.setVolume(musicVolume(), musicVolume());
                player.start();
            }
        } catch (IOException ignored) {
            player = null;
        }

        mBinding = ActivityMainBinding.inflate(getLayoutInflater(), mLayout, false);

        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        layoutParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
        mLayout.addView(mBinding.getRoot(), layoutParams);

        mBinding.getRoot().bringToFront();
        // Only the buttons play: taps on the empty parts of the screen must not reach the table
        mBinding.getRoot().setClickable(true);
        mBinding.getRoot().setOnTouchListener((v, event) -> true);
        mBinding.getRoot().addOnLayoutChangeListener((v, l, t, r, b, ol, ot, or, ob) -> {
            if (r - l != or - ol || b - t != ob - ot) fitPanelsToTable();
        });

        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.Q) {
            // keep the system back gesture from stealing flipper presses at the screen edges
            mBinding.getRoot().addOnLayoutChangeListener((v, l, t, r, b, ol, ot, or, ob) -> {
                int w = r - l;
                int h = b - t;
                int edge = (int) (48 * getResources().getDisplayMetrics().density);
                int height = Math.min(h, (int) (200 * getResources().getDisplayMetrics().density));
                java.util.List<android.graphics.Rect> rects = new java.util.ArrayList<>();
                rects.add(new android.graphics.Rect(0, h - height, edge, h));
                rects.add(new android.graphics.Rect(w - edge, h - height, w, h));
                v.setSystemGestureExclusionRects(rects);
            });
        }

        mBinding.left.setOnTouchListener((v1, event) -> {
            v1.performClick();
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_Z);
                hapticTick();
            }
            if (event.getAction() == MotionEvent.ACTION_UP || event.getAction() == MotionEvent.ACTION_CANCEL) {
                SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_Z);
            }
            return false;
        });


        mBinding.right.setOnTouchListener((v1, event) -> {
            v1.performClick();
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_SLASH);
                hapticTick();
            }
            if (event.getAction() == MotionEvent.ACTION_UP || event.getAction() == MotionEvent.ACTION_CANCEL) {
                SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_SLASH);
            }
            return false;
        });


        mBinding.plunger.setOnTouchListener((v1, event) -> {
            v1.performClick();
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_SPACE);
                hapticTick();
                plungerHeld = true;
                mBinding.plunger.postOnAnimation(plungerPowerUpdater);
            }
            if (event.getAction() == MotionEvent.ACTION_UP || event.getAction() == MotionEvent.ACTION_CANCEL) {
                SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_SPACE);
                plungerHeld = false;
                mBinding.plunger.setPower(0f);
            }
            return false;
        });


        mBinding.playpause.setOnClickListener(view -> setPaused(isPlaying));
        mBinding.pauseoverlay.setOnClickListener(view -> setPaused(false));
        mBinding.exitbtn.setOnClickListener(view -> confirmBackToMenu());

        mBinding.replay.setOnClickListener(view -> {
            final boolean wasPlaying = isPlaying;
            if (wasPlaying) pauseNativeThread();
            new android.app.AlertDialog.Builder(this)
                    .setTitle(R.string.restarttitle)
                    .setMessage(R.string.restartmessage)
                    .setPositiveButton(R.string.yes, (dialog, which) -> restartGame())
                    .setNegativeButton(R.string.no, null)
                    .setOnDismissListener(dialog -> {
                        if (wasPlaying) resumeNativeThread();
                    })
                    .show();
        });


        mBinding.tiltLeft.setOnTouchListener((v1, event) -> {
            v1.performClick();
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_X);
                hapticTick();
            }
            if (event.getAction() == MotionEvent.ACTION_UP || event.getAction() == MotionEvent.ACTION_CANCEL) {
                SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_X);
            }
            return false;
        });

        mBinding.tiltRight.setOnTouchListener((v1, event) -> {
            v1.performClick();
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_PERIOD);
                hapticTick();
            }
            if (event.getAction() == MotionEvent.ACTION_UP || event.getAction() == MotionEvent.ACTION_CANCEL) {
                SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_PERIOD);
            }
            return false;
        });

        mBinding.tiltBottom.setOnTouchListener((v1, event) -> {
            v1.performClick();
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_DPAD_UP);
                hapticTick();
            }
            if (event.getAction() == MotionEvent.ACTION_UP || event.getAction() == MotionEvent.ACTION_CANCEL) {
                SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_DPAD_UP);
            }
            return false;
        });

        mBinding.settingsbtn.setOnClickListener(view -> {
            Intent i = new Intent(this, Settings.class);
            startActivity(i);
        });

        firebaseAnalytics = FirebaseAnalytics.getInstance(this);
        firebaseAnalytics.logEvent(FirebaseAnalytics.Event.APP_OPEN, null);
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        // SDL forwards BACK to the native engine, so catch it here
        if (event.getKeyCode() == KeyEvent.KEYCODE_BACK) {
            if (event.getAction() == KeyEvent.ACTION_UP) confirmBackToMenu();
            return true;
        }
        return super.dispatchKeyEvent(event);
    }

    @Override
    public void onBackPressed() {
        confirmBackToMenu();
    }

    private void setPaused(boolean paused) {
        if (paused == !isPlaying) return;
        isPlaying = !paused;
        if (paused) {
            pauseNativeThread();
            if (player != null && PrefsHelper.getMusic()) player.pause();
        } else {
            resumeNativeThread();
            if (player != null && PrefsHelper.getMusic()) player.start();
        }
        mBinding.pauseoverlay.setVisibility(paused ? View.VISIBLE : View.GONE);
        mBinding.playpause.setImageDrawable(ResourcesCompat.getDrawable(getResources(),
                paused ? R.drawable.play : R.drawable.pause, getTheme()));
    }

    private void goToMenu() {
        leavingToMenu = true;
        Intent menu = new Intent(this, MenuActivity.class);
        menu.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(menu);
        finish();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode != REQUEST_GAME_OVER) return;
        if (resultCode == RESULT_OK) restartGame();
        else goToMenu();
    }

    private void confirmBackToMenu() {
        final boolean wasPlaying = isPlaying;
        if (wasPlaying) pauseNativeThread();
        new android.app.AlertDialog.Builder(this)
                .setTitle(R.string.menutitle)
                .setMessage(R.string.menumessage)
                .setPositiveButton(R.string.yes, (dialog, which) -> goToMenu())
                .setNegativeButton(R.string.no, null)
                .setOnDismissListener(dialog -> {
                    if (wasPlaying && !leavingToMenu) resumeNativeThread();
                })
                .show();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // The native engine cannot be re-initialised, so the game process ends with the game
        if (leavingToMenu) android.os.Process.killProcess(android.os.Process.myPid());
    }

    private void restartGame() {
        SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_F2);
        SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_F2);
        PrefsHelper.setCheatsUsed(false);
    }

    private void hapticTick() {
        if (!PrefsHelper.getHapticFeedback()) return;
        Vibrator vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        if (vibrator == null || !vibrator.hasVibrator()) return;
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            vibrator.vibrate(VibrationEffect.createOneShot(15, VibrationEffect.DEFAULT_AMPLITUDE));
        } else {
            vibrator.vibrate(15);
        }
    }

    /** Copies the files of the chosen table to its own folder, once per app version. */
    private File prepareTableFiles(Table table) {
        File dir = new File(getFilesDir(), table.id);
        File marker = new File(dir, ".version");
        String version = String.valueOf(BuildConfig.VERSION_CODE);
        try {
            if (marker.exists() && version.equals(new String(java.nio.file.Files.readAllBytes(marker.toPath())))
                    && new File(dir, table.datFile).exists()
                    && (table != Table.DRAGON || new File(dir, "BALL_SOURCE.DAT").exists())) return dir;
        } catch (IOException | RuntimeException ignored) {
        }
        dir.mkdirs();
        AssetManager assetManager = getAssets();
        try {
            for (String asset : assetManager.list("")) {
                String[] children = assetManager.list(asset);
                if (children != null && children.length > 0) continue;
                if (table.fullTilt && asset.startsWith("PINBALL.") && !asset.endsWith(".mp3")) continue;
                copyAsset(assetManager, asset, new File(dir, asset));
            }
            if (table == Table.DRAGON) {
                // Dragon's Keep has no steel ball of its own: its ball sprites come from Space Cadet's data
                copyAsset(assetManager, Table.CADET.assetDir() + "/" + Table.CADET.datFile, new File(dir, "BALL_SOURCE.DAT"));
            }
            if (table.assetDir() != null) {
                for (String asset : assetManager.list(table.assetDir())) {
                    copyAsset(assetManager, table.assetDir() + "/" + asset, new File(dir, asset));
                }
            }
            try (OutputStream os = new FileOutputStream(marker)) {
                os.write(version.getBytes());
            }
        } catch (IOException e) {
            Log.e(TAG, "Unable to prepare " + table.id, e);
        }
        return dir;
    }

    private void copyAsset(AssetManager assetManager, String asset, File target) {
        try (InputStream is = assetManager.open(asset);
             OutputStream os = new FileOutputStream(target)) {
            byte[] buffer = new byte[8192];
            int len;
            while ((len = is.read(buffer)) != -1) {
                os.write(buffer, 0, len);
            }
        } catch (IOException e) {
            Log.e(TAG, "Unable to copy " + asset, e);
        }
    }

    private void setFullscreen() {
        int ui_Options = View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
        getWindow().getDecorView().setSystemUiVisibility(ui_Options);
    }

    private final StateHelper.IStateListener mStateListener = new StateHelper.IStateListener() {
        @Override
        public void onStateChanged(int state) {
            applyAudio();
            putTranslations();
            putString(26, " ");  // no player name on screen //TODO abstract ids

            if (state == GameState.RUNNING) {
                gamesInSession++;
                runOnUiThread(() -> firebaseAnalytics.logEvent(FirebaseAnalytics.Event.LEVEL_START, null));
            }

            if (state == GameState.FINISHED) {
                runOnUiThread(() -> firebaseAnalytics.logEvent(FirebaseAnalytics.Event.LEVEL_END, null));
            }
        }

        @Override
        public void onBallInPlungerChanged(boolean isBallInPlunger) {
            runOnUiThread(() -> showPlunger(isBallInPlunger));
        }

        @Override
        public void onHighScorePresented(int score) {
            // Called once when a game ends
            HighScoreHandler.postHighScore(score);
            final boolean cheated = PrefsHelper.getCheatsUsed();
            runOnUiThread(() -> {
                int rank = 0;
                if (!cheated && score > 0) {
                    rank = ScoreBoard.add(MainActivity.this, currentTable.id,
                            score, System.currentTimeMillis());
                }
                Intent intent = new Intent(MainActivity.this, HighScoresActivity.class);
                intent.putExtra(HighScoresActivity.EXTRA_TABLE, currentTable.id);
                intent.putExtra(HighScoresActivity.EXTRA_SCORE, score);
                intent.putExtra(HighScoresActivity.EXTRA_RANK, rank);
                intent.putExtra(HighScoresActivity.EXTRA_GAME_OVER, true);
                startActivityForResult(intent, REQUEST_GAME_OVER);
            });
        }

        @Override
        public int onHighScoreRequested() {
            return PrefsHelper.getHighScore();
        }

        @Override
        public void onStringPresented(String str, int type) {
            if (!PrefsHelper.getShowMessages()) return;
            final String fstr = str.replace("\n", " ");
            if (type == 1) runOnUiThread(() -> mBinding.missiontxt.setText(fstr));
            else runOnUiThread(() -> mBinding.infotxt.setText(fstr));
        }

        @Override
        public void onClearText(int type) {
            if (type == 1) runOnUiThread(() -> mBinding.missiontxt.setText(""));
            else runOnUiThread(() -> mBinding.infotxt.setText(""));
        }

        @Override
        public void onScorePosted(int score) {
            String str = "" + score;
            runOnUiThread(() -> mBinding.txtscore.setText(str));
        }

        @Override
        public void onBallCountUpdated(int count) {
            ballCount = count;
            if (!PrefsHelper.getRemainingBalls()) {
                String str = getString(R.string.balls, count);
                runOnUiThread(() -> mBinding.ballstxt.setText(str));
            }
        }

        @Override
        public void onCheatsUsed() {
            PrefsHelper.setCheatsUsed(true);
            runOnUiThread(() -> firebaseAnalytics.logEvent("cheat_used", null));
        }

        @Override
        public void onGameReady() {
            isGameReady = true;
            // the table's painting is only drawn once the table runs: keep a copy for the menu and the HUD
            new android.os.Handler(android.os.Looper.getMainLooper()).postDelayed(MainActivity.this::saveSidebarArt, 3000);
        }

        @Override
        public void onRemainingBallsRequested(int balls) {
            remainingBalls = balls;
            if (PrefsHelper.getRemainingBalls()) {
                String str = getString(R.string.remainingballs, balls);
                runOnUiThread(() -> mBinding.ballstxt.setText(str));
            }
        }
    };

    @Override
    protected void onResume() {
        super.onResume();
        StateHelper.INSTANCE.addListener(mStateListener);
        // the ball may have been placed in the plunger before this screen was listening
        mStateListener.onBallInPlungerChanged(StateHelper.INSTANCE.isBallInPlunger());
        if (PrefsHelper.getMusic()) {
            if (player == null) {
                player = new MediaPlayer();
                try {
                    AssetFileDescriptor afd = getAssets().openFd("PINBALL.mp3");
                    player.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
                    player.prepare();
                    player.setLooping(true);
                    player.setVolume(musicVolume(), musicVolume());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }

            player.start();
        }

        if (!isPlaying) pauseNativeThread();
        if (isGameReady) {
            applyAudio();
        }
        PrefsHelper.setCheatsUsed(checkCheatsUsed());
        setFullscreen();
        setTiltButtons();
        tintHud();
        applySidebarArt();
        setCustomFonts();
        setBallsText();
    }

    /** The round plunger button appears (and pulses) only while a ball waits to be shot. */
    private void showPlunger(boolean ballWaiting) {
        if (plungerPulse != null) {
            plungerPulse.cancel();
            plungerPulse = null;
        }
        mBinding.plunger.setScaleX(1f);
        mBinding.plunger.setScaleY(1f);
        mBinding.plunger.setVisibility(ballWaiting ? View.VISIBLE : View.INVISIBLE);
        if (ballWaiting) {
            plungerPulse = android.animation.ObjectAnimator.ofPropertyValuesHolder(mBinding.plunger,
                    android.animation.PropertyValuesHolder.ofFloat(View.SCALE_X, 1f, 1.1f),
                    android.animation.PropertyValuesHolder.ofFloat(View.SCALE_Y, 1f, 1.1f));
            plungerPulse.setDuration(700);
            plungerPulse.setRepeatMode(android.animation.ValueAnimator.REVERSE);
            plungerPulse.setRepeatCount(android.animation.ValueAnimator.INFINITE);
            plungerPulse.start();
        }
    }

    /** Fits the control panels into the margins above and below the table, which keeps its aspect ratio. */
    private void fitPanelsToTable() {
        View root = mBinding.getRoot();
        int width = root.getWidth();
        int height = root.getHeight();
        if (width == 0 || height == 0) return;
        int margin = (int) ((height - width * TABLE_ASPECT) / 2);
        float density = getResources().getDisplayMetrics().density;
        margin = Math.max(margin, (int) (120 * density));
        ViewGroup.LayoutParams top = mBinding.toppanel.getLayoutParams();
        top.height = margin;
        mBinding.toppanel.setLayoutParams(top);
        ViewGroup.LayoutParams back = mBinding.backdrop.getLayoutParams();
        back.height = margin;
        mBinding.backdrop.setLayoutParams(back);
        ViewGroup.LayoutParams bottom = mBinding.bottompanel.getLayoutParams();
        bottom.height = margin;
        mBinding.bottompanel.setLayoutParams(bottom);

        // The floating shooter window is a square centered on the table, 40% of its width: the button goes just below it
        int windowBottom = height / 2 + (int) (width * 0.40f / 2);
        androidx.constraintlayout.widget.ConstraintLayout.LayoutParams plunger =
                (androidx.constraintlayout.widget.ConstraintLayout.LayoutParams) mBinding.plunger.getLayoutParams();
        plunger.topMargin = windowBottom + (int) (10 * density) + 20;
        mBinding.plunger.setLayoutParams(plunger);
    }

    private void setBallsText() {
        mBinding.ballslabel.setText(PrefsHelper.getRemainingBalls() ? R.string.hud_balls_left : R.string.hud_ball);
        if (!PrefsHelper.getRemainingBalls()) {
            String str = getString(R.string.balls, ballCount);
            mBinding.ballstxt.setText(str);
        } else {
            String str = getString(R.string.remainingballs, remainingBalls);
            mBinding.ballstxt.setText(str);
        }
    }

    private void setTiltButtons() {
        mBinding.tiltrow.setVisibility(PrefsHelper.getTiltButtons() ? View.VISIBLE : View.GONE);
    }

    /** The score and balls bar takes the outline color of the table's own sidebar text. */
    private void tintHud() {
        int stroke = (int) (1.5f * getResources().getDisplayMetrics().density);
        android.graphics.drawable.Drawable bg = mBinding.hudbar.getBackground().mutate();
        if (bg instanceof android.graphics.drawable.GradientDrawable) {
            ((android.graphics.drawable.GradientDrawable) bg).setStroke(stroke, currentTable.accent);
        }
        mBinding.hudsplit.setBackgroundColor((currentTable.accent & 0x00FFFFFF) | 0x55000000);
    }

    private void setCustomFonts() {
        if (PrefsHelper.getCustomFonts()) {
            mBinding.ballstxt.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.ballstxt.setTextColor(currentTable.accent);
            mBinding.txtscore.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.txtscore.setTextColor(currentTable.accent);
            mBinding.infotxt.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.infotxt.setTextColor(currentTable.accent);
            mBinding.missiontxt.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.missiontxt.setTextColor(currentTable.accent);
            mBinding.plunger.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.tiltLeft.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.tiltLeft.setTextColor(currentTable.accent);
            mBinding.tiltBottom.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.tiltBottom.setTextColor(currentTable.accent);
            mBinding.tiltRight.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.tiltRight.setTextColor(currentTable.accent);
            mBinding.left.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.left.setTextColor(currentTable.accent);
            mBinding.right.setTypeface(ResourcesCompat.getFont(getContext(), R.font.bauhauscheavy));
            mBinding.right.setTextColor(currentTable.accent);
        } else {
            mBinding.ballstxt.setTypeface(Typeface.DEFAULT);
            mBinding.ballstxt.setTextColor(Color.WHITE);
            mBinding.txtscore.setTypeface(Typeface.DEFAULT);
            mBinding.txtscore.setTextColor(Color.WHITE);
            mBinding.infotxt.setTypeface(Typeface.DEFAULT);
            mBinding.infotxt.setTextColor(Color.WHITE);
            mBinding.missiontxt.setTypeface(Typeface.DEFAULT);
            mBinding.missiontxt.setTextColor(Color.WHITE);
            mBinding.plunger.setTypeface(Typeface.DEFAULT);
            mBinding.tiltLeft.setTypeface(Typeface.DEFAULT);
            mBinding.tiltLeft.setTextColor(Color.WHITE);
            mBinding.tiltBottom.setTypeface(Typeface.DEFAULT);
            mBinding.tiltBottom.setTextColor(Color.WHITE);
            mBinding.tiltRight.setTypeface(Typeface.DEFAULT);
            mBinding.tiltRight.setTextColor(Color.WHITE);
            mBinding.left.setTypeface(Typeface.DEFAULT);
            mBinding.left.setTextColor(Color.WHITE);
            mBinding.right.setTypeface(Typeface.DEFAULT);
            mBinding.right.setTextColor(Color.WHITE);
        }
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
            mBinding.infotxt.setVisibility(View.GONE);
            mBinding.missiontxt.setVisibility(View.GONE);
            mBinding.hudbar.setVisibility(View.GONE);
        } else {
            mBinding.infotxt.setVisibility(View.VISIBLE);
            mBinding.missiontxt.setVisibility(View.VISIBLE);
            mBinding.hudbar.setVisibility(View.VISIBLE);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        StateHelper.INSTANCE.removeListener(mStateListener);
        if (player != null) player.pause();
    }

    @Override
    protected void onStop() {
        Bundle bndl = new Bundle();
        bndl.putInt("games_per_session", gamesInSession);
        firebaseAnalytics.logEvent("games_per_session", bndl);
        super.onStop();
    }

    @Override
    protected String getMainFunction() {
        return "main";
    }

    @Override
    protected String[] getLibraries() {
        return new String[] {
                "SDL2",
                "SpaceCadetPinball"
        };
    }

    private void putTranslations() {
        int[] ids = getResources().getIntArray(R.array.gametexts_idxs);
        String[] texts = getResources().getStringArray(R.array.gametexts_strings);
        for (int i = 0; i < ids.length; i++) {
            putString(ids[i], texts[i]);
        }
    }

    private native void initNative(String dataPath, String datFile, boolean fullTilt);

    private native void setSoundEnabled(boolean enabled);

    private native void setSoundVolume(int volume);

    private native int[] captureSidebarArt();

    private File sidebarArtFile() {
        return new File(getFilesDir(), currentTable.id + "/" + ArtFiles.SIDEBAR);
    }

    /** Copies the sidebar painting out of the engine once, so it can also be used by the menu. */
    private void saveSidebarArt() {
        File file = sidebarArtFile();
        if (!file.exists()) {
            int[] data = captureSidebarArt();
            if (data == null || data.length < 3) return;
            Bitmap art = Bitmap.createBitmap(data, 2, data[0], data[0], data[1], Bitmap.Config.ARGB_8888);
            try (java.io.FileOutputStream out = new java.io.FileOutputStream(file)) {
                art.compress(Bitmap.CompressFormat.PNG, 100, out);
            } catch (IOException ignored) {
                return;
            }
        }
        applySidebarArt();
    }

    /** Shows the saved painting behind the top panel and on the pause screen. */
    private void applySidebarArt() {
        File file = sidebarArtFile();
        if (!file.exists()) return;
        Bitmap art = android.graphics.BitmapFactory.decodeFile(file.getAbsolutePath());
        if (art == null) return;
        mBinding.pauseart.setImageBitmap(art);
    }

    private native float getPlungerPower();

    private float musicVolume() {
        return PrefsHelper.getMusicVolume() / 100f;
    }

    private void applyAudio() {
        setSoundEnabled(PrefsHelper.getSoundFx());
        setSoundVolume(PrefsHelper.getSoundVolume() * 128 / 100);
        if (player != null) player.setVolume(musicVolume(), musicVolume());
    }
    private native void putString(int id, String str);

    private native boolean checkCheatsUsed();
}