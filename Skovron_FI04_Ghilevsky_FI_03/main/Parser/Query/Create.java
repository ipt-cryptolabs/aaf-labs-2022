package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public class Create implements SQLCommand {

    public Create(String sql){

    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }

    /**
     * check col names in sql query, if smth wrong throw
     * @return array of col names in sql order
     * @throws IllegalArgumentException
     */
    public String[] getNameOfColum() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }
}
