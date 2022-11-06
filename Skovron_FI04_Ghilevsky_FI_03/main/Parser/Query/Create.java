package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public class Create implements SQLCommand {

    private final String TableName;
    private final String[] NameOfColumn;

    public Create(String sql) throws IllegalArgumentException{
        checkSqlQuery(sql);
        String StrNameOfColumn = sql.substring(sql.indexOf("(")+1, sql.indexOf(")"));

        TableName = sql.substring(7, sql.indexOf("(")).trim();
        NameOfColumn = StrNameOfColumn.replaceAll("\\W+"," ").split(" ");
    }

    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName == null || TableName.equals(""))
            throw new IllegalArgumentException("Error: Empty table name (Create)");

        return TableName;
    }

    public String[] getNameOfColum() throws IllegalArgumentException {
        for (String i: NameOfColumn) {
            if(i == null || i.equals(""))
                throw new IllegalArgumentException("Error: Empty Column name (Create)");
        }

        return NameOfColumn;
    }

    public void checkSqlQuery(String sql) throws IllegalArgumentException { //доделать
        if(!sql.replaceAll("[^()]", "").equals("()")){
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Error 2)");
        }
    }

}
