package com.fexed.spacecadetpinball;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;

import androidx.appcompat.widget.AppCompatButton;

/** Round button that draws a ring around itself showing how far the plunger is pulled back. */
public class PlungerButton extends AppCompatButton {
    private final Paint track = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint arc = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final RectF bounds = new RectF();
    private float power;

    public PlungerButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        float density = getResources().getDisplayMetrics().density;
        track.setStyle(Paint.Style.STROKE);
        track.setStrokeWidth(6 * density);
        track.setColor(0x33FFFFFF);
        arc.setStyle(Paint.Style.STROKE);
        arc.setStrokeWidth(6 * density);
        arc.setStrokeCap(Paint.Cap.ROUND);
    }

    /** @param power 0..1 */
    public void setPower(float power) {
        this.power = power;
        invalidate();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        float inset = track.getStrokeWidth() / 2;
        bounds.set(inset, inset, getWidth() - inset, getHeight() - inset);
        canvas.drawArc(bounds, 0, 360, false, track);
        if (power > 0f) {
            // green at low power, through amber to red at full power
            int g = (int) (200 * Math.min(1f, 2f * (1f - power)) + 55);
            int r = (int) (255 * Math.min(1f, 2f * power));
            arc.setColor(0xFF000000 | (r << 16) | (g << 8) | 0x30);
            canvas.drawArc(bounds, -90, 360f * power, false, arc);
        }
    }
}
