package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import java.util.Arrays;

public class Create implements SQLCommand {
    private String TableName;
    private String[] NameOfColumn;
    public Create(String sql){
        String[] sql_ = sql.replaceAll("\\W+"," ").split(" ");
        TableName = sql_[1];
        NameOfColumn = Arrays.copyOfRange(sql_, 2, sql_.length);
        System.out.println("Table " + TableName + " has been created.");
    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName == null || TableName == "") {
            throw new UnsupportedOperationException("Error: Empty table name");} // ??
        return TableName;
    }

    /**
     * check col names in sql query, if smth wrong throw
     * @return array of col names in sql order
     * @throws IllegalArgumentException
     */
    public String[] getNameOfColum() throws IllegalArgumentException {
        if(NameOfColumn == null) {
            throw new UnsupportedOperationException("Error: Empty Column name");} // ??
        return NameOfColumn;
    }
}
