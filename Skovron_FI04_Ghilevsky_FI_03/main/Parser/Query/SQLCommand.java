package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public interface SQLCommand {
    /**
     * check name in sql query, else throw
     * @return name of table
     * @throws IllegalArgumentException
     */
    String getTableName() throws IllegalArgumentException;
}
