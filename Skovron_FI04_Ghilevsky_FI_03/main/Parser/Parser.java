package Skovron_FI04_Ghilevsky_FI_03.main.Parser;

import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.*;

public class Parser {

    private final String sqlQuery;

    private static final String CREATE   = "CREATE";
    private static final String INSERT   = "INSERT";
    private static final String INSERT_INTO = "INSERT INTO";
    private static final String SELECT   = "SELECT";

    private final String primeCommand;
    private String tableName;
    private int[]  rows;

    public Parser(String sqlQuery){
        this.sqlQuery = sqlQuery;

        primeCommand = queryRead()[0].toUpperCase();
    }
    // треба трохи переробити, бо не всі варанти обробляються
    // наприклад insert into + чутливй до регістру
    public SQLCommand createSQLCommand() throws Exception { // lexical analysis
        return switch (primeCommand) {
            case CREATE              -> new Create(sqlQuery);
            case INSERT, INSERT_INTO -> new Insert(sqlQuery);
            case SELECT              -> new Select(sqlQuery);
            default -> throw new Exception("Invalid SQL syntax (Error 1)");
        };
    }

    private String[] queryRead(){
        String _sqlQuery = sqlQuery.replaceAll("[,();]"," ");

        return _sqlQuery.replaceAll("\\s+"," ").split(" ");
    }

}
