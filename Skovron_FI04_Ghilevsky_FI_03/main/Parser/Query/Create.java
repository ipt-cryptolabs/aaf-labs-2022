package Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query;

import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Create implements SQLCommand {

    private final String TableName;
    private final String[] NameOfColumn;

    public Create(String sql) throws IllegalArgumentException {
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

        TableName = sqlList.get(1);
        sqlList.pop();
        sqlList.pop();
        NameOfColumn = sqlList.toArray(new String[0]);
    }

    @Override
    public String getTableName() {
        return TableName;
    }

    public String[] getNameOfColum() {
        return NameOfColumn;
    }

    @Override
    public void checkSqlQuery(String sql) throws IllegalArgumentException {
        if (!sql.replaceAll("[^()]", "").equals("()")) {
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Creation Error 1)");
        }

        String sql_ = ReplaceSpacesInQuotes(sql).replaceAll("\"", "");

        String[] split1 = sql_.substring(0, sql_.indexOf('(')).split("\\s+");
        if (split1.length == 1) {
            throw new IllegalArgumentException("Error: Empty table name");
        }
        if (split1.length > 2) {
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Creation Error 2)");
        }

        String[] split2 = sql_.substring(sql_.indexOf('(') + 1, sql_.indexOf(')')).replaceAll("\\s+", "").split(",");
        if (split2.length == 0) {
            throw new IllegalArgumentException("Error: Empty Column name (Create)");
        }
        for (String i : split2) {
            if (i.equals("")) {
                throw new IllegalArgumentException("Error: Empty Column name (Create)");
            }
        }

        String[] split3 = sql_.substring(sql_.indexOf(')'), sql_.indexOf(';')).split("\\s+");
        if (split3.length > 1 || !split3[0].equals(")")) {
            throw new IllegalArgumentException("Error: Invalid SQL syntax (Creation Error 3)");
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
