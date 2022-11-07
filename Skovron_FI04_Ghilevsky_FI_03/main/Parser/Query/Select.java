package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public class Select implements SQLCommand{

    private boolean flag = false;
    private String TableName;

    public Select(String sql) throws IllegalArgumentException {
        String[] sql_ = sql.replaceAll(";", "").split("\\s+");

        for(int i = 1; i <sql_.length; i++){
            if(sql_[i].equalsIgnoreCase("FROM")){
                TableName = sql_[i+1];
            }
        }

        if(sql_[0].equalsIgnoreCase("SELECT") && sql_[1].equalsIgnoreCase("FROM"))
            flag = true;
    }

    @Override
    public String getTableName() throws IllegalArgumentException {
        if(TableName.equalsIgnoreCase("")
                || TableName.equalsIgnoreCase("GROUP_BY")
                || TableName.equalsIgnoreCase("WHERE")
        ){
            throw new IllegalArgumentException("Error: Empty table name (Select)");
        }
        return TableName;
    }

    public boolean isSelectAll() {
        if (flag){
            flag = false;
            return true;
        }
        return false;
    }

    public boolean isSelectWhereValue() {
        throw new UnsupportedOperationException();
    }

    public boolean isSelectWhereColumn() {
        throw new UnsupportedOperationException();
    }

    public boolean isSelectGroupBy(){
        throw new UnsupportedOperationException();
    }

    /**
     * поки не трогати
     * @return
     */
    public String[][] selectGroupBy(){
        throw new UnsupportedOperationException();
    }

    /**
     * @return [0] імя стовбця по якому треба порівнювати
     *         [1] int по якому треба порівнювати
     * @throws IllegalArgumentException
     */
    public String[] selectWhereValue() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }

    /**
     * @return [0] імя 1 стовбця по якому треба порівнювати
     *         [1] імя 2 стовбця по якому треба порівнювати
     *         1 стовбець йде першим*
     * @throws IllegalArgumentException
     */
    public String[] selectWhereCol() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }

    public String select() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }

}