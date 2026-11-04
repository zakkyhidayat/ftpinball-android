package com.fexed.spacecadetpinball;

import android.content.Context;
import android.os.Bundle;
import android.widget.SeekBar;

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
        mBinding.plungerzoom.setChecked(PrefsHelper.getPlungerZoom());
        mBinding.plungerzoom.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setPlungerZoom(checked));
        mBinding.soundfx.setChecked(PrefsHelper.getSoundFx());
        mBinding.soundfx.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setSoundFx(checked));
        mBinding.music.setChecked(PrefsHelper.getMusic());
        mBinding.music.setOnCheckedChangeListener((b, checked) -> PrefsHelper.setMusic(checked));

        mBinding.soundvol.setProgress(PrefsHelper.getSoundVolume());
        mBinding.soundvol.setOnSeekBarChangeListener(new VolumeListener(true));
        mBinding.musicvol.setProgress(PrefsHelper.getMusicVolume());
        mBinding.musicvol.setOnSeekBarChangeListener(new VolumeListener(false));

        mBinding.verstxtv.setText(getString(R.string.current_ver) + " " + BuildConfig.VERSION_NAME + " (" + BuildConfig.VERSION_CODE + ")");
    }

    private static class VolumeListener implements SeekBar.OnSeekBarChangeListener {
        private final boolean effects;

        VolumeListener(boolean effects) {
            this.effects = effects;
        }

        @Override
        public void onProgressChanged(SeekBar bar, int progress, boolean fromUser) {
            if (effects) PrefsHelper.setSoundVolume(progress);
            else PrefsHelper.setMusicVolume(progress);
        }

        @Override
        public void onStartTrackingTouch(SeekBar bar) {
        }

        @Override
        public void onStopTrackingTouch(SeekBar bar) {
        }
    }

    @Override
    public boolean onSupportNavigateUp() {
        finish();
        return true;
    }
}
