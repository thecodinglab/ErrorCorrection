package ch.kbw.GUI.crc;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.util.Duration;

import java.util.ArrayList;

public class CRCController {

    private Timeline timeline;
    private float speed = 1;
    private ArrayList<Step> steps;
    private int index;

    @FXML
    private TextField input, polynom;

    @FXML
    private Button run;
    private boolean running;

    @FXML
    private VBox content;

    @FXML
    public void handleRun(ActionEvent event) {

        if (running) {
            run.setText("run");
            timeline.stop();
        }

        int input = Integer.parseInt(this.input.getText());
        int polynomial = Integer.parseInt(this.polynom.getText());

        steps = new ArrayList<>();
        index = 0;

        // TODO: implement visualization
        int crc = 0; // Set the initial value to zero
        crc ^= input << 24; // XOR current byte value with crc

        steps.add(new Step(polynomial, this.polynom.getLength(), crc));

        for (byte j = 0; j < 8; j++) { // Repeat for 8 bits in current byte
            if ((crc & 0x80000000) != 0) { // Check if most significant bit is set

                // If it is: Shift the crc one bit to the left to discard the most significant bit
                // and XOR the crc with the polynomial (generator)
                crc = (crc << 1) ^ polynomial;
            }
            else {
                // If not shift the crc 1 bit to the left
                crc <<= 1;
            }
        }
    }

    @FXML
    public void stepForeward(ActionEvent event) {
        this.content.getChildren().add(steps.get(index++));
    }

    @FXML
    public void stepBackward(ActionEvent event) {
        this.content.getChildren().remove(index--);
    }
}
