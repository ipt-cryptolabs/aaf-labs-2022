package src.main.Controller;

import src.main.Parser.Parser;

import java.util.Objects;
import java.util.Scanner;

public class View {

    public String readQueryToArray(){

        Scanner scanner = new Scanner(System.in);
        StringBuilder query = new StringBuilder();

        while (scanner.hasNextLine()) {
            query.append(" ").append(scanner.nextLine());

            if (Objects.equals(query.substring(query.length() - 1), ";"))
                break;
        }

        scanner.close();
        return query.toString();
    }

    public void action() {

    }

    public void run() {

        while (true) {
            Parser parser = new Parser(readQueryToArray());
            action();
        }

    }
}

