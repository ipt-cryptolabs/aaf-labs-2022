package Skovron_FI04_Ghilevsky_FI_03.main.Controller;

import Skovron_FI04_Ghilevsky_FI_03.main.Controller.SelectTable.CreateSelectTable;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Table;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Parser;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.*;

import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class View {

    private final ArrayList<Table> tables = new ArrayList<>();

    public void run() {
        while (true) {
            Parser parser = new Parser(readQueryFromConsole());
            action(parser);
        }
    }

    public void action(Parser parser) {
        try {
            SQLCommand sqlCommand = parser.createSQLCommand();

            if (sqlCommand instanceof Create) {
                Table table = new Table(
                        sqlCommand.getTableName(),
                        ((Create) sqlCommand).getNameOfColum());

                if (!isTableExist(sqlCommand.getTableName())) {
                    tables.add(table);

                    System.out.println("table " + sqlCommand.getTableName() + " has been created");
                } else {
                    throw new Exception("Table already exist (Error Create)");
                }
            } else if (sqlCommand instanceof Insert) {
                String name = sqlCommand.getTableName();
                Table table;

                if (isTableExist(name)) {
                    table = findTable(name);
                    table.rowInsert(((Insert) sqlCommand).getRow());

                    System.out.println("1 row has been insert in " + name);
                } else {
                    throw new NoSuchElementException("No such table (Error Insert)");
                }
            } else if (sqlCommand instanceof Select) {
                String name = sqlCommand.getTableName();
                Table table;

                if (isTableExist(name)) {
                    table = findTable(name);
                    CreateSelectTable selectTable = new CreateSelectTable((Select) sqlCommand, table);
                    selectTable.select();
                } else {
                    throw new NoSuchElementException("No such table (Error Select)");
                }
            } else {
                System.out.println("Unexpected error");
            }

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    private String readQueryFromConsole() {
        Scanner scanner = new Scanner(System.in);
        StringBuilder query = new StringBuilder();

        while (scanner.hasNextLine()) {
            query.append(" ").append(scanner.nextLine());

            if (query.indexOf(";") > -1) {
                query.delete(query.indexOf(";") + 1, query.length());
                break;
            }
        }

        return query.toString();
    }

    private Table findTable(String name) {
        Table table = null;

        for (Table value : tables)
            if (value.getTableName().equals(name))
                table = value;

        return table;
    }

    private boolean isTableExist(String name) {
        for (Table table : tables)
            if (table.getTableName().equals(name))
                return true;

        return false;
    }
}