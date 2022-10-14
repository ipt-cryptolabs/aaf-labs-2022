package src.main.Parser;

import src.main.Parser.QueryAsk.Create;
import src.main.Parser.QueryAsk.Insert;
import src.main.Parser.QueryAsk.SQLCommand;
import src.main.Parser.QueryAsk.Select;

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

    public SQLCommand createSQLCommand() throws Exception { // processing
        return switch (primeCommand) {
            case CREATE -> new Create();
            case INSERT -> new Insert();
            case SELECT -> new Select();
            default -> throw new Exception();
        };
    }

    private String[] queryRead(){
        String _sqlQuery = sqlQuery.replaceAll("[,();]"," ");

        return _sqlQuery.replaceAll("\\s+"," ").split(" ");
    }

}
