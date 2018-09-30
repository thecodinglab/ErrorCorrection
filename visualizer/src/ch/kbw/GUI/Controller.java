package ch.kbw.GUI;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.Tab;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class Controller implements Initializable {

    @FXML
    Tab crc, hamming;


    @Override
    public void initialize(URL location, ResourceBundle resources) {
        try {
            this.crc.setContent(FXMLLoader.load(this.getClass().getResource("crc/crc.fxml")));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
