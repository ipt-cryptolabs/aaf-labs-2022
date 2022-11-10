package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

public class Select implements SQLCommand{

    private boolean isSelectAll         = false;
    private boolean isSelectWhereValue  = false;
    private boolean isSelectWhereColumn = false;
    private boolean isSelectGroupBy     = false;
    private String tableName;

    public Select(String sql) throws IllegalArgumentException {
        String[] sql_ = sql.replaceAll(";", "").split("\\s+");

        for(int i = 1; i <sql_.length; i++){
            if(sql_[i].equalsIgnoreCase("FROM")){
                tableName = sql_[i+1];
            }
        }

        if(sql_[0].equalsIgnoreCase("SELECT") && sql_[1].equalsIgnoreCase("FROM"))
            isSelectAll = true;
    }

    @Override
    public String getTableName() throws IllegalArgumentException {
        if(tableName.equalsIgnoreCase("")
                || tableName.equalsIgnoreCase("GROUP_BY")
                || tableName.equalsIgnoreCase("WHERE")
        ){
            throw new IllegalArgumentException("Error: Empty table name (Select)");
        }
        return tableName;
    }

    @Override
    public void checkSqlQuery(String sql) throws IllegalArgumentException {

    }

    public boolean isSelectAll() {
        return isSelectAll;
    }

    public boolean isSelectWhereValue() {
        return isSelectWhereValue;
    }

    public boolean isSelectWhereColumn() {
        return isSelectWhereColumn;
    }

    public boolean isSelectGroupBy(){
        return isSelectGroupBy;
    }

    /**
     * повератає імена колонок по яких треба робити групу
     * select ... from tableName group_by groupName1, groupName2, ..., groupNameN;
     * @return [0]   імя 1 групи
     *         [1]   імя 2 групи
     *         ...   -----||-----
     *         [n-1] імя N-1 групи
     */
    public String[] getGroupNames() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }

    /**
     * повератає імена агрегуючих колонок
     * select aggFun(colName1), ..., aggFun(colNameK)  from tableName group_by ...;
     * @return [0]   aggFun1(colName1)
     *         [1]   aggFun2(colName2)
     *         ...   -----||-----
     *         [K-1] aggFunK(colNameK)
     * наприклад {"COUNT(id)", ...}
     */
    public String[] getAggMethods() throws IllegalArgumentException {
        throw new UnsupportedOperationException();
    }

    /**
     * повератає імена агрегуючих колонок, але тільки функції
     * select aggFun(colName1), ..., aggFun(colNameK)  from tableName group_by ...;
     * @return [0]   aggFun1
     *         [1]   aggFun2
     *         ...   -----||-----
     *         [K-1] aggFunK
     * наприклад {"COUNT", "MAX", "AVG", ...}
     * P.S можуть бути лише COUNT, MAX, AVG
     */
    public String[] getAggFun(){
        throw new UnsupportedOperationException();
    }

    /**
     * повератає імена агрегуючих колонок, але тільки імена колонок
     * select aggFun(colName1), ..., aggFun(colNameK)  from tableName group_by ...;
     * @return [0]   colName1
     *         [1]   colName2
     *         ...   -----||-----
     *         [K-1] colNameK
     * наприклад {"id", "age", "weight", ...}
     */
    public String[] getAggCol(){
        throw new UnsupportedOperationException();
    }

    /**
     * @return [0] імя стовбця по якому треба порівнювати
     *         [1] int по якому треба порівнювати
     */
    public String[] selectWhereValue() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }

    /**
     * @return [0] імя 1 стовбця по якому треба порівнювати
     *         [1] імя 2 стовбця по якому треба порівнювати
     *         1 стовбець йде першим*
     */
    public String[] selectWhereCol() throws IllegalArgumentException{
        throw new UnsupportedOperationException();
    }

}