package Skovron_FI04_Ghilevsky_FI_03.test.ParserTest;

import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class SelectTest {
        @Test
        void regularSelectCase1Test(){
            Select select = new Select("SELECT FROM students");
            Assertions.assertEquals("students", select.getTableName());
        }

        @Test
        void isSelectAllTest(){
            Select select = new Select("SELECT FROM students");
            Assertions.assertTrue(select.isSelectAll());
        }

}
