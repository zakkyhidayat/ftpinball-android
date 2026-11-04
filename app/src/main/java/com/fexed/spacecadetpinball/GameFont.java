package com.fexed.spacecadetpinball;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;

/** The picture fonts of a table: its score digits and its message letters, copied from the table's own data. */
final class GameFont {
    private final Bitmap[] digits = new Bitmap[10];
    private final Bitmap[] chars = new Bitmap[128];
    private int height;
    private int gap;
    private final Paint paint = new Paint(Paint.FILTER_BITMAP_FLAG);

    /** Parses the array the game process captured: ten digits, then {height, gap, count, {code, glyph...}}. */
    static GameFont fromArray(int[] a) {
        GameFont font = new GameFont();
        int[] pos = {0};
        for (int i = 0; i < 10; i++) font.digits[i] = readGlyph(a, pos);
        font.height = a[pos[0]++];
        font.gap = a[pos[0]++];
        int count = a[pos[0]++];
        for (int i = 0; i < count; i++) {
            int code = a[pos[0]++];
            font.chars[code & 0x7F] = readGlyph(a, pos);
        }
        return font;
    }

    private static Bitmap readGlyph(int[] a, int[] pos) {
        int w = a[pos[0]++];
        int h = a[pos[0]++];
        Bitmap bmp = Bitmap.createBitmap(a, pos[0], w, w, h, Bitmap.Config.ARGB_8888);
        pos[0] += w * h;
        return bmp;
    }

    static void save(File file, int[] data) throws IOException {
        try (DataOutputStream out = new DataOutputStream(new BufferedOutputStream(new FileOutputStream(file)))) {
            out.writeInt(data.length);
            for (int v : data) out.writeInt(v);
        }
    }

    static GameFont load(File file) {
        if (!file.exists()) return null;
        try (DataInputStream in = new DataInputStream(new BufferedInputStream(new FileInputStream(file)))) {
            int[] data = new int[in.readInt()];
            for (int i = 0; i < data.length; i++) data[i] = in.readInt();
            return fromArray(data);
        } catch (IOException | RuntimeException e) {
            return null;
        }
    }

    int getHeight() {
        return Math.max(height, digits[0] != null ? digits[0].getHeight() : 1);
    }

    private Bitmap glyph(char c, boolean digitsOnly) {
        if (c >= '0' && c <= '9') return digits[c - '0'];
        return digitsOnly ? null : chars[c & 0x7F];
    }

    /** Width of the text in font pixels. */
    float measure(String text, boolean digitsOnly) {
        float w = 0;
        for (int i = 0; i < text.length(); i++) {
            Bitmap g = glyph(text.charAt(i), digitsOnly);
            w += (g != null ? g.getWidth() : height / 3f) + gap;
        }
        return Math.max(0, w - gap);
    }

    /** Draws the text with its top left corner at x, y, every font pixel scaled by scale. */
    void draw(Canvas canvas, String text, float x, float y, float scale, boolean digitsOnly) {
        for (int i = 0; i < text.length(); i++) {
            Bitmap g = glyph(text.charAt(i), digitsOnly);
            if (g == null) {
                x += (height / 3f + gap) * scale;
                continue;
            }
            float top = y + (getHeight() - g.getHeight()) * scale / 2f;
            canvas.drawBitmap(g, null, new android.graphics.RectF(x, top, x + g.getWidth() * scale, top + g.getHeight() * scale), paint);
            x += (g.getWidth() + gap) * scale;
        }
    }
}
