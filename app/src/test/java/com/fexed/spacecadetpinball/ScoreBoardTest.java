package com.fexed.spacecadetpinball;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class ScoreBoardTest {
    @Test
    public void formatsScoresWithCommas() {
        assertEquals("0", ScoreBoard.format(0));
        assertEquals("999", ScoreBoard.format(999));
        assertEquals("1,000", ScoreBoard.format(1000));
        assertEquals("1,585,000", ScoreBoard.format(1585000));
    }

    @Test
    public void addsCommasToLongNumbersInMessages() {
        assertEquals("Total Bonus 10,000", ScoreBoard.commas("Total Bonus 10000"));
        assertEquals("Jackpot 1,000,000 and 3 balls", ScoreBoard.commas("Jackpot 1000000 and 3 balls"));
        assertEquals("Ball 3", ScoreBoard.commas("Ball 3"));
    }

    @Test
    public void leavesDecimalsAndGroupedNumbersAlone() {
        assertEquals("pi 3.14159", ScoreBoard.commas("pi 3.14159"));
        assertEquals("1,000", ScoreBoard.commas("1,000"));
    }
}
