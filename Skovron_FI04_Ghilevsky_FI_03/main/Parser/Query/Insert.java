package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;


import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static java.lang.Integer.parseInt;

public class Insert implements SQLCommand {
    private boolean isInto = false;
    private final String TableName;
    private final Row Row;

    public Insert(String sql) throws IllegalArgumentException {
        String[] checkInto = sql.split("\\s+");
        if (checkInto[1].equalsIgnoreCase("INTO")) {
            isInto = true;
        }
        checkSqlQuery(sql.trim());

        String sql_ = sql.trim()
                .replaceAll("[()]", " ")
                .replaceAll(",", " ")
                .replaceAll(";", " ")
                .replaceAll("\\s+", " ");

        LinkedList<String> sqlList = new LinkedList<>();
        Matcher m = Pattern.compile("([^\"]\\S*|\".+?\")\\s*").matcher(sql_);
        while (m.find())
            if (m.group().split("\\s+").length == 1) {
                sqlList.add(m.group(1).replace("\"", ""));
            } else {
                sqlList.add(m.group(1));
            }

        if (isInto) {
            isInto = false;
            sqlList.pop();
            sqlList.pop();
        } else {
            sqlList.pop();
        }

        TableName = sqlList.get(0);

        int[] IntRows = new int[sqlList.size() - 1];

        for (int i = 0; i < sqlList.size() - 1; i++) {
            IntRows[i] = parseInt(sqlList.get(i + 1));
        }

        Row = new Row(IntRows);
    }

    @Override
    public String getTableName() {
        return TableName;
    }

    public Row getRow() {
        return Row;
    }

    @Override
    public void checkSqlQuery(String sql) throws IllegalArgumentException {
        if (!sql.replaceAll("[^()]", "").equals("()")) {
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Insertion Error 1)");
        }

        String sql_ = ReplaceSpacesInQuotes(sql).replaceAll("\"", "");

        String[] split1 = sql_.substring(0, sql_.indexOf('(')).split("\\s+");
        if (isInto) {
            if (split1.length == 2) {
                throw new IllegalArgumentException("Error: Empty table name");
            }
            if (split1.length > 3) {
                throw new IllegalArgumentException("Error: Invalid SQL syntax (Insertion Error 2)");
            }
        } else {
            if (split1.length == 1) {
                throw new IllegalArgumentException("Error: Empty table name");
            }
            if (split1.length > 2) {
                throw new IllegalArgumentException("Error: Invalid SQL syntax (Insertion Error 2)");
            }
        }

        String[] split2 = sql_.substring(sql_.indexOf('(') + 1, sql_.indexOf(')')).replaceAll("\\s+", "").split(",");
        if (split2.length == 0) {
            throw new IllegalArgumentException("Error: Empty Column name (Insert)");
        }

        for (String i : split2) {
            if (i.equals("")) {
                throw new IllegalArgumentException("Error: Empty Column name (Insert)");
            }
        }

        String[] split3 = sql_.substring(sql_.indexOf(')'), sql_.indexOf(';')).split("\\s+");
        if (split3.length > 1 || !split3[0].equals(")")) {
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Creation Error 2)");
        }
    }

    private static String ReplaceSpacesInQuotes(String input) {
        StringBuilder sb = new StringBuilder();
        StringBuilder quotedWord = new StringBuilder();
        boolean inQuotes = false;
        for (int i = 0, imax = input.length(); i < imax; i++) {
            char c = input.charAt(i);
            if (c == '"') {
                if (!inQuotes) {
                    quotedWord.setLength(0);
                } else {
                    String qw = quotedWord.toString();
                    sb.append(qw.replace(" ", "_"));
                }
                inQuotes = !inQuotes;
            }
            if (inQuotes) {
                quotedWord.append(c);
            } else {
                sb.append(c);
            }
        }
        return sb.toString();
    }
}
