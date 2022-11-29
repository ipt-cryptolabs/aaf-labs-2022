package Skovron_FI04_Ghilevsky_FI_03.main.Parser;

import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.*;

public class Parser {

    private final String sqlQuery;
    private String primeCommand;

    private static final String CREATE = "CREATE";
    private static final String INSERT = "INSERT";
    private static final String INSERT_INTO = "INSERT INTO";
    private static final String SELECT = "SELECT";

    public Parser(String sqlQuery) {
        this.sqlQuery = sqlQuery.trim();

        primeCommand = queryRead()[0].toUpperCase();
    }

    public SQLCommand createSQLCommand() throws Exception {
        primeCommand = primeCommand.toUpperCase();

        if (primeCommand.equals(CREATE))
            return new Create(sqlQuery);
        if (primeCommand.equals(INSERT) || primeCommand.equals(INSERT_INTO))
            return new Insert(sqlQuery);
        if (primeCommand.equals(SELECT))
            return new Select(sqlQuery);
        else
            throw new Exception("Invalid SQL syntax (Error 1)");
    }

    private String[] queryRead() {
        String _sqlQuery = sqlQuery.replaceAll("[,();]", " ");

        return _sqlQuery.replaceAll("\\s+", " ").split(" ");
    }

}