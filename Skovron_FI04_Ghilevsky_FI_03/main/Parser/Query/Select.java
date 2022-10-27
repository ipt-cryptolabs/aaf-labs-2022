package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public class Select implements SQLCommand{

    public Select(String sql){

    }

    @Override
    public String getTableName() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }
}