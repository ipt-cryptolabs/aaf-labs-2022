package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;

import java.util.ArrayList;

public class Insert implements SQLCommand{

    public Insert(String sql){

    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }
    public int getNumberOfRows(){
        throw new UnsupportedOperationException();
    }
    public ArrayList<Row> getRows() throws IllegalArgumentException { // треба ще подумати
        throw new UnsupportedOperationException();
    }
}
