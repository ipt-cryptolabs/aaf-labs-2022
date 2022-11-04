package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;

import java.util.ArrayList;
import java.util.Arrays;

import static java.lang.Integer.parseInt;

public class Insert implements SQLCommand{

    private String TableName;
    private int NumberOfRows;
    private String[] Rows;

    public Insert(String sql){
        String[] sql_ = sql.replaceAll("\\W+"," ").split(" ");
        TableName = sql_[1];
        NumberOfRows = parseInt(sql_[2]);
        Rows = Arrays.copyOfRange(sql_, 3, sql_.length);
    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName == null || TableName == "") {
            throw new UnsupportedOperationException("Error: Empty table name");} //??
        return TableName;
    }

    /**
     * if smth wrong return -1;
     * @return number of rows
     */
    public int getNumberOfRows(){
        //throw new UnsupportedOperationException();
        return NumberOfRows;
    }

    /**
     * check sql data and wrap to Row type
     * if smth wrong throw, text message
     * @return ArrayList<Row> in sql order
     * @throws IllegalArgumentException
     */
    public ArrayList<Row> getRows() throws IllegalArgumentException { // треба ще подумати

        int[] IntRows = new int[Rows.length];
        for(int i = 0; i < Rows.length; i++){
            IntRows[i] = parseInt(Rows[i]);
        }
        //throw new UnsupportedOperationException();
        ArrayList<Row> Rows_ = new ArrayList<>(Arrays.asList(new Row(IntRows)));
        return Rows_;
    }
}
