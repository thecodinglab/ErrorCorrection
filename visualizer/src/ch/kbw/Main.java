package ch.kbw;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("GUI/frame.fxml"));
        primaryStage.setTitle("Visualizer");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
        primaryStage.setMinWidth(800);
        primaryStage.setMinHeight(400);
        primaryStage.setMaxWidth(800);
    }

    public static void main(String[] args) {
        launch(args);
    }
}
