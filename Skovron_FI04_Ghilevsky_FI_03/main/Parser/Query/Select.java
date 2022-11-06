package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import java.lang.annotation.Documented;
import java.nio.channels.UnsupportedAddressTypeException;

public class Select implements SQLCommand{

    private String TableName;

    public Select(String sql){
        String[] sql_ = sql.split("\\s+");

        for(int i = 1; i <sql_.length; i++){
            if(sql_[i].equalsIgnoreCase("FROM")){
                TableName = sql_[i+1];
            }
        }


    }
    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName.equalsIgnoreCase("")
                || TableName.equalsIgnoreCase("GROUP_BY")
                || TableName.equalsIgnoreCase("WHERE")
        ){
            throw new UnsupportedOperationException("Error: Empty table name");
        }
        return TableName;
    }

    /**
     *  check if sql query is type of:
     *  select from tableName
     * @return is needed display whole table
     */
    public boolean isSelectAll() {
        throw new UnsupportedOperationException();
    }

    /**
     * @return int по якому треба порівнювати
     * @throws IllegalArgumentException
     */
    public int selectWhereNum() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }

    /**
     * поки сам не знаю, що тут треба робити,тому @Deprecated
     * @return column name
     * @throws IllegalArgumentException
     */
    @Deprecated
    public String selectWhereCol() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }

    public String select() throws IllegalArgumentException{
        throw new UnsupportedAddressTypeException();
    }

}