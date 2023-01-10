package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public interface SQLCommand {

    void checkSqlQuery(String sql) throws IllegalArgumentException;

    String getTableName();

}
