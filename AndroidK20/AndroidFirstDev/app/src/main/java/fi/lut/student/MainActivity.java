package fi.lut.student;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button addButton = (Button) findViewById(R.id.addButton);
        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText firstNumberTxt = (EditText) findViewById(R.id.editText);
                EditText secondNumberTxt = (EditText) findViewById(R.id.editText2);
                TextView resultTextView = (TextView) findViewById(R.id.resultTextView);

                int num1 = Integer.parseInt(firstNumberTxt.getText().toString());
                int num2 = Integer.parseInt(secondNumberTxt.getText().toString());
                int result = num1 + num2;

                resultTextView.setText(result);
            }
        });
    }
}
