package Skovron_FI04_Ghilevsky_FI_03.main.Parser;

import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.*;

public class Parser {

    private final String sqlQuery;
    private final String[] sqlQueryArray;

    private static final String CREATE   = "CREATE";
    private static final String DELETE   = "DELETE";
    private static final String INSERT   = "INSERT";
    private static final String INTO     = "INTO";
    private static final String SELECT   = "SELECT";
    private static final String FROM     = "FROM";
    private static final String WHERE    = "WHERE";
    private static final String GROUP_BY = "GROUP_BY"; //  maybe in enum??

    private final String primeCommand;
    private String tableName;
    private int[]  rows;

    public Parser(String sqlQuery){
        this.sqlQuery = sqlQuery;

        sqlQueryArray = queryRead();

        primeCommand = sqlQueryArray[0].toUpperCase();
    }

    public SQLCommand createSQLCommand() throws Exception { // lexical analysis
        return switch (primeCommand) {
            case CREATE -> new Create(sqlQuery);
            case INSERT -> new Insert(sqlQuery);
            case SELECT -> new Select(sqlQuery);
            default -> throw new Exception("Invalid SQL syntax (Error 1)");
        };
    }

    private String[] queryRead(){
        String _sqlQuery = sqlQuery.replaceAll("[,();]"," ");

        return _sqlQuery.replaceAll("\\s+"," ").split(" ");
    }

}
