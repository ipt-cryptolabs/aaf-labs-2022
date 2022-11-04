package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static java.lang.Integer.parseInt;

public class Insert implements SQLCommand{

    private final String TableName;
    private String[] Rows;

    public Insert(String sql){
        String[] sql_ = sql.replaceAll("\\W+"," ").split(" ");
        TableName = sql_[1];
        Rows = Arrays.copyOfRange(sql_, 3, sql_.length);
    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName == null || TableName.equals("")) {
            throw new IllegalArgumentException("Error: Empty table name");} //??

        return TableName;
    }

    /**
     * check sql data and wrap to Row type
     * if smth wrong throw, text message
     * @return ArrayList<Row> in sql order
     * @throws IllegalArgumentException
     */
    @Deprecated
    public ArrayList<Row> getRows() throws IllegalArgumentException {
        int[] IntRows = new int[Rows.length];

        for(int i = 0; i < Rows.length; i++){
            IntRows[i] = parseInt(Rows[i]);
        }
        return new ArrayList<>(List.of(new Row(IntRows)));
    }

    public Row getRow() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }
}
