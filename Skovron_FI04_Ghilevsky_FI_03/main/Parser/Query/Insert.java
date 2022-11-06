package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static java.lang.Integer.parseInt;

public class Insert implements SQLCommand{

    private final String TableName;
    private Row Row;

    public Insert(String sql){
        TableName = sql.substring(7, sql.indexOf("(")).trim();
        String StrRow = sql.substring(sql.indexOf("(")+1, sql.indexOf(")"));
        String[] Rows = StrRow.replaceAll("\\W+"," ").split(" ");

        int[] IntRows = new int[Rows.length];
        try {

            for (int i = 0; i < Rows.length; i++) {
                IntRows[i] = parseInt(Rows[i]);
            }
        } catch(NumberFormatException e){
            System.out.println(e);
        }
        Row = new Row(IntRows);
    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName == null || TableName.equals("")) {
            throw new IllegalArgumentException("Error: Empty table name");}

        return TableName;
    }

    /**
     * check sql data and wrap to Row type
     * if smth wrong throw, text message
     * @return ArrayList<Row> in sql order
     * @throws IllegalArgumentException
     */

//    @Deprecated
//    public ArrayList<Row> getRows() throws IllegalArgumentException {
//        int[] IntRows = new int[Rows.length];
//
//        for(int i = 0; i < Rows.length; i++){
//            IntRows[i] = parseInt(Rows[i]);
//        }
//        return new ArrayList<>(List.of(new Row(IntRows)));
//    }

    public Row getRow() throws IllegalArgumentException {
        //throw new IllegalArgumentException("Error: Empty row value");
        return Row;
    }
}
