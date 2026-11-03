package com.fexed.spacecadetpinball;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.Bundle;
import android.os.Looper;
import android.text.Editable;
import android.text.TextWatcher;
import android.text.method.LinkMovementMethod;
import android.view.KeyEvent;
import android.view.View;
import android.widget.TextView;

import com.fexed.spacecadetpinball.databinding.ActivityMainBinding;
import com.fexed.spacecadetpinball.databinding.ActivitySettingsBinding;

import org.libsdl.app.SDLActivity;
import org.w3c.dom.Text;

import java.security.PublicKey;
import java.util.Random;

public class Settings extends AppCompatActivity {

    private ActivitySettingsBinding mBinding;

    private void addDescription(TextView label, int descRes) {
        android.text.SpannableStringBuilder sb = new android.text.SpannableStringBuilder(label.getText());
        int start = sb.length();
        sb.append("\n").append(getString(descRes));
        sb.setSpan(new android.text.style.RelativeSizeSpan(0.75f), start, sb.length(), android.text.Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        sb.setSpan(new android.text.style.ForegroundColorSpan(getResources().getColor(R.color.description_grey)), start, sb.length(), android.text.Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        label.setText(sb);
    }

    @Override
    public boolean onSupportNavigateUp() {
        finish();
        return true;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        PrefsHelper.setPrefs(getSharedPreferences("com.fexed.spacecadetpinball", android.content.Context.MODE_PRIVATE));
        mBinding = ActivitySettingsBinding.inflate(getLayoutInflater());
        View view = mBinding.getRoot();
        setContentView(view);
        if (getSupportActionBar() != null) {
            getSupportActionBar().setTitle(R.string.settings_title);
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        }
        addDescription(mBinding.textView5, R.string.desc_cstmfnts);
        addDescription(mBinding.textView15, R.string.desc_plungerpopup);
        addDescription(mBinding.textView24, R.string.desc_showmessages);
        addDescription(mBinding.textView19, R.string.desc_remainingballs);
        addDescription(mBinding.textView20, R.string.desc_fullscreenplunger);
        addDescription(mBinding.textView22, R.string.desc_music);
        addDescription(mBinding.textView23, R.string.desc_hapticfeedback);

        int score = PrefsHelper.getHighScore();
        String txt = score + "";
        mBinding.highscoretxtv.setText(txt);

        txt = BuildConfig.VERSION_NAME + " (" + BuildConfig.VERSION_CODE + ")";
        mBinding.verstxtv.setText(txt);

        boolean tiltenabled = PrefsHelper.getTiltButtons();
        mBinding.tiltbtns.setChecked(tiltenabled);
        mBinding.tiltbtns.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setTiltButtons(b);
        });

        boolean customfonts = PrefsHelper.getCustomFonts();
        mBinding.cstmfnts.setChecked(customfonts);
        mBinding.cstmfnts.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setCustomFonts(b);
        });

        boolean plungerpopup = PrefsHelper.getPlungerPopup();
        mBinding.plungerpopup.setChecked(plungerpopup);
        mBinding.plungerpopup.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setPlungerPopup(b);
        });

        mBinding.showmessages.setChecked(PrefsHelper.getShowMessages());
        mBinding.showmessages.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setShowMessages(b);
        });

        boolean remainingballs = PrefsHelper.getRemainingBalls();
        mBinding.remainingballs.setChecked(remainingballs);
        mBinding.remainingballs.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setRemainingBalls(b);
        });

        boolean fullScreenPlunger = PrefsHelper.getFullScreenPlunger();
        mBinding.fullscreenplunger.setChecked(fullScreenPlunger);
        mBinding.fullscreenplunger.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setFullScreenPlunger(b);

            if (!b) {
                PrefsHelper.setShouldShowBottomPlunger(true);
            }
        });

        boolean music = PrefsHelper.getMusic();
        mBinding.music.setChecked(music);
        mBinding.music.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setMusic(b);
        });

        mBinding.hapticfeedback.setChecked(PrefsHelper.getHapticFeedback());
        mBinding.hapticfeedback.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setHapticFeedback(b);
        });

        mBinding.inpttxtusername.setText(PrefsHelper.getUsername("Player 1"));
        mBinding.inpttxtusername.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                PrefsHelper.setUsername(charSequence.toString());
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });

        mBinding.gplaytxtv.setOnClickListener(v -> {
            Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://play.google.com/store/apps/dev?id=6687966458279653723"));
            startActivity(browserIntent);
        });
        mBinding.githubtxtv.setOnClickListener(v -> {
            Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/fexed/Pinball-on-Android/releases/latest"));
            startActivity(browserIntent);
        });

        mBinding.soundfx.setChecked(PrefsHelper.getSoundFx());
        mBinding.soundfx.setOnCheckedChangeListener((compoundButton, b) -> {
            PrefsHelper.setSoundFx(b);
        });

        if (PrefsHelper.getCheatsUsed()) {
            mBinding.cheatindicatorlbl.setText(R.string.cheat_used);
            mBinding.cheatAlertSttngs.setVisibility(View.VISIBLE);
        }
        else {
            mBinding.cheatindicatorlbl.setText(R.string.cheat_notused);
            mBinding.cheatAlertSttngs.setVisibility(View.INVISIBLE);
        }

        mBinding.gmaxbtn.setOnClickListener(v -> {
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_G);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_G);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_X);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_X);
        });

        mBinding.rmaxbtn.setOnClickListener(v -> {
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_R);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_R);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_X);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_X);
        });

        mBinding.onemaxbtn.setOnClickListener(v -> {
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_1);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_1);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_X);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_X);
        });

        mBinding.bmaxbtn.setOnClickListener(v -> {
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_B);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_B);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_X);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_X);
        });

        mBinding.omaxbtn.setOnClickListener(v -> {
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_O);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_O);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_X);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_X);
        });

        mBinding.lmaxbtn.setOnClickListener(v -> {
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_L);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_L);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_M);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_A);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_X);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_X);
        });

        mBinding.hdntestbtn.setOnClickListener(v -> {
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_H);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_H);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_I);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_I);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_D);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_D);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_D);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_D);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_E);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_E);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_N);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_N);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_SPACE);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_SPACE);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_T);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_T);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_E);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_E);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_S);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_S);
            SDLActivity.onNativeKeyDown(KeyEvent.KEYCODE_T);
            SDLActivity.onNativeKeyUp(KeyEvent.KEYCODE_T);
        });

    }
}
