package ch.kbw.GUI.crc;

import javafx.scene.control.Label;
import javafx.scene.layout.Pane;

public class Step extends Pane {

    private int polynomial;
    private int leading;
    private int value;

    public Step(int polynomial, int leading, int value) {
        this.polynomial = polynomial;
        this.leading = leading;
        this.value = value;

        Label v = new Label("" + Integer.toBinaryString(value));
        this.getChildren().addAll(v);
    }

    public int getPolynomial() {
        return polynomial;
    }

    public void setPolynomial(int polynomial) {
        this.polynomial = polynomial;
    }

    public int getLeading() {
        return leading;
    }

    public void setLeading(int leading) {
        this.leading = leading;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
