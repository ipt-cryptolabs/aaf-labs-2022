package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public class Create implements SQLCommand {

    public Create(String sql){

    }

    @Override
    public String getTableName() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }

    public String[] getNameOfColum() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }
}
