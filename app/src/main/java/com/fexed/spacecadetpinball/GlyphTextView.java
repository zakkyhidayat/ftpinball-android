package com.fexed.spacecadetpinball;

import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.view.Gravity;

import androidx.appcompat.widget.AppCompatTextView;

/** A text view that draws with the table's own picture font once it has one, and with a normal font before that. */
public class GlyphTextView extends AppCompatTextView {
    private GameFont gameFont;
    private boolean digitsOnly;

    public GlyphTextView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    void setGameFont(GameFont font, boolean digitsOnly) {
        this.gameFont = font;
        this.digitsOnly = digitsOnly;
        requestLayout();
        invalidate();
    }

    private float glyphScale(String text, float availW, float availH) {
        float target = digitsOnly ? availH * 0.8f : getTextSize() * 0.95f;
        float scale = target / gameFont.getHeight();
        float width = gameFont.measure(text, digitsOnly) * scale;
        if (availW > 0 && width > availW) scale *= availW / width;
        return scale;
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        if (gameFont == null) return;
        int mode = MeasureSpec.getMode(widthMeasureSpec);
        if (mode == MeasureSpec.EXACTLY) return;
        String text = getText().toString();
        float scale = glyphScale(text, 0, getMeasuredHeight() - getPaddingTop() - getPaddingBottom());
        int w = (int) Math.ceil(gameFont.measure(text, digitsOnly) * scale) + getPaddingLeft() + getPaddingRight();
        setMeasuredDimension(resolveSize(w, widthMeasureSpec), getMeasuredHeight());
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (gameFont == null) {
            super.onDraw(canvas);
            return;
        }
        String text = getText().toString();
        float availW = getWidth() - getPaddingLeft() - getPaddingRight();
        float availH = getHeight() - getPaddingTop() - getPaddingBottom();
        float scale = glyphScale(text, availW, availH);
        float w = gameFont.measure(text, digitsOnly) * scale;
        float h = gameFont.getHeight() * scale;
        int gravity = getGravity() & Gravity.HORIZONTAL_GRAVITY_MASK;
        float x = getPaddingLeft() + (gravity == Gravity.END || gravity == Gravity.RIGHT ? availW - w
                : gravity == Gravity.START || gravity == Gravity.LEFT ? 0 : (availW - w) / 2f);
        float y = getPaddingTop() + (availH - h) / 2f;
        gameFont.draw(canvas, text, x, y, scale, digitsOnly);
    }
}
