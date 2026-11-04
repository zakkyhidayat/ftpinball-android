package com.fexed.spacecadetpinball;

import android.content.Context;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;

import androidx.appcompat.app.AppCompatActivity;

import com.fexed.spacecadetpinball.databinding.ActivitySettingsBinding;

public class Settings extends AppCompatActivity {
    private ActivitySettingsBinding mBinding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        PrefsHelper.setPrefs(getSharedPreferences("com.fexed.spacecadetpinball", Context.MODE_PRIVATE));
        mBinding = ActivitySettingsBinding.inflate(getLayoutInflater());
        setContentView(mBinding.getRoot());
        if (getSupportActionBar() != null) {
            getSupportActionBar().setTitle(R.string.settings_title);
            getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        }

        mBinding.inpttxtusername.setText(PrefsHelper.getUsername("Player 1"));
        mBinding.inpttxtusername.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                String name = s.toString().trim();
                PrefsHelper.setUsername(name.isEmpty() ? "Player 1" : name);
            }

            @Override
            public void afterTextChanged(Editable s) {
            }
        });

        mBinding.tiltbtns.setChecked(PrefsHelper.getTiltButtons());
        mBinding.tiltbtns.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setTiltButtons(checked));
        mBinding.hapticfeedback.setChecked(PrefsHelper.getHapticFeedback());
        mBinding.hapticfeedback.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setHapticFeedback(checked));
        mBinding.cstmfnts.setChecked(PrefsHelper.getCustomFonts());
        mBinding.cstmfnts.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setCustomFonts(checked));
        mBinding.showmessages.setChecked(PrefsHelper.getShowMessages());
        mBinding.showmessages.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setShowMessages(checked));
        mBinding.remainingballs.setChecked(PrefsHelper.getRemainingBalls());
        mBinding.remainingballs.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setRemainingBalls(checked));
        mBinding.soundfx.setChecked(PrefsHelper.getSoundFx());
        mBinding.soundfx.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setSoundFx(checked));
        mBinding.music.setChecked(PrefsHelper.getMusic());
        mBinding.music.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setMusic(checked));

        mBinding.verstxtv.setText(getString(R.string.current_ver) + " " + BuildConfig.VERSION_NAME + " (" + BuildConfig.VERSION_CODE + ")");
    }

    @Override
    public boolean onSupportNavigateUp() {
        finish();
        return true;
    }
}
