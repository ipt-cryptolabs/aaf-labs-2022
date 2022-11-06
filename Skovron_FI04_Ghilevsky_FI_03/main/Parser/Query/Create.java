package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public class Create implements SQLCommand {
    private final String TableName;
    private final String[] NameOfColumn;

    public Create(String sql) throws IllegalArgumentException{
        checkSqlQuery(sql);
        TableName = sql.substring(7, sql.indexOf("(")).trim();
        String StrNameOfColumn = sql.substring(sql.indexOf("(")+1, sql.indexOf(")"));
        NameOfColumn = StrNameOfColumn.replaceAll("\\W+"," ").split(" ");
    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName == null || TableName.equals("")) {
            throw new IllegalArgumentException("Error: Empty table name");}
        return TableName;
    }

    /**
     * check col names in sql query, if smth wrong throw
     * @return array of col names in sql order
     * @throws IllegalArgumentException
     */
    public String[] getNameOfColum() throws IllegalArgumentException {
        for (String i: NameOfColumn
             ) {
            if(i == null || i.equals("")){
                throw new IllegalArgumentException("Error: Empty Column name");
            }
        }
        return NameOfColumn;
    }


    public void checkSqlQuery(String sql) throws IllegalArgumentException { //доделать
        if(!sql.replaceAll("[^()]", "").equals("()")){
            throw new IllegalArgumentException("Error: Wrong sqlQuery");
        }
    }

}
