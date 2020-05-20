package fi.lut.shoppinglist;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

public class ProductDetails extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_product_details);

        Intent in = getIntent();

        String name = in.getStringExtra("fi.lut.PRODUCT_NAME");
        String info = in.getStringExtra("fi.lut.OTHER_INFO");

        TextView namedisp = (TextView) findViewById(R.id.productNameTextView);
        TextView infodisp = (TextView) findViewById(R.id.infoTextView);

        namedisp.setText(name);
        infodisp.setText(info);

    }
}
