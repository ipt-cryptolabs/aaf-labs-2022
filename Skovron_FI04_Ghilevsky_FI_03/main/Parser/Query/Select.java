package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Stack;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class Select implements SQLCommand {

    private boolean isSelectAll = false;
    private boolean isSelectWhereValue = false;
    private boolean isSelectWhereColumn = false;
    private boolean isSelectGroupBy = false;
    private final String tableName;
    private final String[] groupNames;
    private final String[] aggMethods;
    private final String[] aggFun;
    private final String[] aggCol;
    private final String[] whereValue;
    private final String[] whereCol;

    public Select(String sql) throws IllegalArgumentException {
        checkSqlQuery(sql);
        String sql_ = sql.trim()
                .replaceAll("[()]", " ")
                .replaceAll(",", " ")
                .replaceAll(";", " ")
                .replaceAll("=", " ")
                .replaceAll("\\s+", " ");

        ArrayList<String> sqlList = new ArrayList<>();
        Matcher m = Pattern.compile("([^\"]\\S*|\".+?\")\\s*").matcher(sql_);
        while (m.find())
            if (m.group().split("\\s+").length == 1) {
                sqlList.add(m.group(1).replace("\"", ""));
            } else {
                sqlList.add(m.group(1));
            }

        LinkedList<String> aggMethods_ = new LinkedList<>();
        LinkedList<String> aggFun_ = new LinkedList<>();
        LinkedList<String> aggCol_ = new LinkedList<>();
        LinkedList<String> whereCol_ = new LinkedList<>();
        LinkedList<String> whereValue_ = new LinkedList<>();
        LinkedList<String> groupNames_ = new LinkedList<>();

        int counter = 1;
        int i = 0;
        while (!sqlList.get(counter).equalsIgnoreCase("FROM")) {
            aggFun_.add(sqlList.get(counter));
            counter += 1;
            aggCol_.add(sqlList.get(counter));
            counter += 1;
            aggMethods_.add(aggFun_.get(i) + "(" + aggCol_.get(i) + ")");
            i += 1;
        }

        counter += 1;
        tableName = sqlList.get(counter);
        counter += 1;

        if (counter < sqlList.size() && sqlList.get(counter).equalsIgnoreCase("WHERE")) {
            counter += 1;
            while (counter < sqlList.size() && !sqlList.get(counter).equalsIgnoreCase("GROUP_BY")) {
                whereCol_.add(sqlList.get(counter));
                counter += 1;
                whereValue_.add(sqlList.get(counter));
                counter += 1;
            }
        }

        counter += 1;

        while (counter < sqlList.size()) {
            groupNames_.add(sqlList.get(counter));
            counter += 1;
        }

        groupNames = groupNames_.toArray(new String[0]);
        aggMethods = aggMethods_.toArray(new String[0]);
        aggFun = aggFun_.toArray(new String[0]);
        aggCol = aggCol_.toArray(new String[0]);
        whereValue = whereValue_.toArray(new String[0]);
        whereCol = whereCol_.toArray(new String[0]);

        if (aggFun_.isEmpty() && groupNames_.isEmpty() && whereCol_.isEmpty()) {
            isSelectAll = true;
        }

        if (!groupNames_.isEmpty()) {
            isSelectGroupBy = true;
        }

        if (!whereCol_.isEmpty()) {
            if (isNumeric(whereValue_.get(0))) {
                isSelectWhereValue = true;
            } else {
                isSelectWhereColumn = true;
            }
        }
    }

    private static boolean isNumeric(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    @Override
    public String getTableName() throws IllegalArgumentException {
        if (tableName.equalsIgnoreCase("")
                || tableName.equalsIgnoreCase("GROUP_BY")
                || tableName.equalsIgnoreCase("WHERE")
        ) {
            throw new IllegalArgumentException("Error: Empty table name (Select)");
        }
        return tableName;
    }

    @Override
    public void checkSqlQuery(String sql) throws IllegalArgumentException {
        String sql_ = sql.trim()
                .replaceAll("[()]", " ")
                .replaceAll(",", " ")
                .replaceAll(";", " ")
                .replaceAll("=", " ")
                .replaceAll("\\s+", " ");

        ArrayList<String> sqlList = new ArrayList<>();
        Matcher m = Pattern.compile("([^\"]\\S*|\".+?\")\\s*").matcher(sql_);
        while (m.find()) {
            if (m.group().split("\\s+").length == 1) {
                sqlList.add(m.group(1).replace("\"", ""));
            } else {
                sqlList.add(m.group(1));
            }
        }

        boolean checkFrom = false;
        int counter = 1;
        for (int i = 1; i < sqlList.size(); i++) {
            if (sqlList.get(i).equalsIgnoreCase("FROM")) {
                checkFrom = true;
                counter = i;
                break;
            }
            if (sqlList.get(i).equalsIgnoreCase("WHERE") || sqlList.get(i).equalsIgnoreCase("GROUP_BY")) {
                throw new IllegalArgumentException("Error: Invalid SQL order");
            }
            counter += 1;
        }

        if (!checkFrom) {
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Selection Error 1)"); //missing "from"
        }

        boolean checkAggFun = false;
        String brackets = sql.replaceAll("[^()]", "");
        if (!balancedBrackets(brackets)) {
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Selection Error 2)"); //brackets placed incorrectly
        }
        if (!brackets.equals("")) {
            checkAggFun = true;
            ArrayList<String> AggFun_ = new ArrayList<>();
            for (int i = 1; i < counter; i++) {
                AggFun_.add(sqlList.get(i));
            }
            if (AggFun_.size() % 2 == 1) {
                throw new IllegalArgumentException("Error: Invalid func name or empty column name");
            }
            int i = 0;
            while (i < AggFun_.size()) {
                if (!AggFun_.get(i).equals("COUNT") && !AggFun_.get(i).equals("MAX") && !AggFun_.get(i).equals("AVG")) {
                    throw new IllegalArgumentException("Error: Invalid func name");
                }
                i += 1;
                if (AggFun_.get(i).equals("") || AggFun_.get(i).equals("COUNT") || AggFun_.get(i).equals("MAX") || AggFun_.get(i).equals("AVG")) {
                    throw new IllegalArgumentException("Error: Empty or invalid column name ");
                }
                i += 1;
            }
        }

        counter += 1;
        if (counter == sqlList.size()) {
            throw new IllegalArgumentException("Error: Empty table name");
        }
        if (sqlList.get(counter).equals("") || sqlList.get(counter).equals("WHERE") || sqlList.get(counter).equals("GROUP_BY")) {
            throw new IllegalArgumentException("Error: Empty table name");
        }


        counter += 1;
        if (counter < sqlList.size()) {
            if (sqlList.get(counter).equalsIgnoreCase("WHERE")) {
                if (!sql.contains("=")) {
                    throw new IllegalArgumentException("Error: Invalid SQL syntax (Selection Error 4)"); //missed "="
                }
                checkWhere(counter, sqlList);
            } else if (sqlList.get(counter).equalsIgnoreCase("GROUP_BY")) {
                if (!checkAggFun) {
                    throw new IllegalArgumentException("Error: Empty func name");
                }
                checkGroupBy(counter, sqlList);
            } else {
                throw new IllegalArgumentException("Error: Invalid SQL syntax (Selection Error 3)");
            }
        }

    }

    private void checkWhere(int counter, ArrayList<String> sqlList) {
        counter += 3;
        if (counter < sqlList.size()) {
            if (!sqlList.get(counter).equalsIgnoreCase("GROUP_BY")) {
                throw new IllegalArgumentException("Error: Invalid SQL syntax (Selection Error 5)");
            } else {
                checkGroupBy(counter, sqlList);
            }
        }
    }

    private void checkGroupBy(int counter, ArrayList<String> sqlList) {
        counter += 1;
        if (counter == sqlList.size()) {
            throw new IllegalArgumentException("Error: Empty group name");
        }
        while (counter < sqlList.size()) {
            if (sqlList.get(counter).equalsIgnoreCase("WHERE")) {
                throw new IllegalArgumentException("Error: Invalid SQL order");
            }
            counter += 1;
        }
    }

    private static boolean balancedBrackets(String input) {
        if ((input.length() % 2) == 1) return false;
        else {
            Stack<Character> stack = new Stack<>();
            for (char bracket : input.toCharArray()) {
                if (bracket == '(') {
                    stack.push(')');
                    continue;
                }
                if (stack.isEmpty() || bracket != stack.peek()) return false;
                stack.pop();
            }
            return stack.isEmpty();
        }
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

    public boolean isSelectGroupBy() {
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
        if (groupNames == null)
            throw new UnsupportedOperationException();

        return groupNames;
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
        if (aggMethods == null)
            throw new UnsupportedOperationException("Error: Empty Agg Methods (Select)");

        return aggMethods;
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
    public String[] getAggFun() {
        if (aggFun == null)
            throw new UnsupportedOperationException("Error: Empty Agg Function (Select)");

        return aggFun;
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
    public String[] getAggCol() {
        if (aggCol == null)
            throw new UnsupportedOperationException();

        return aggCol;
    }

    /**
     * @return [0] імя стовбця по якому треба порівнювати
     *         [1] int по якому треба порівнювати
     */
    public String[] selectWhereValue() throws IllegalArgumentException {
        if (whereValue == null)
            throw new UnsupportedOperationException();

        return whereValue;
    }

    /**
     * @return [0] імя 1 стовбця по якому треба порівнювати
     *         [1] імя 2 стовбця по якому треба порівнювати
     *         1 стовбець йде першим*
     */
    public String[] selectWhereCol() throws IllegalArgumentException {
        if (whereCol == null)
            throw new UnsupportedOperationException();

        return whereCol;
    }

}