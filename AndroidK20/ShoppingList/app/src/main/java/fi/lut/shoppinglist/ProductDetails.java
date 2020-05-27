package fi.lut.shoppinglist;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.ByteArrayOutputStream;

public class ProductDetails extends AppCompatActivity {

    private boolean mRemoveItemFlag = false;
    Button removeItemButton;
    int db_position;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_product_details);

        Intent in = getIntent();

        String amount = in.getStringExtra("fi.lut.PRODUCT_AMOUNT");
        String name = in.getStringExtra("fi.lut.PRODUCT_NAME");
        String price = in.getStringExtra("fi.lut.PRODUCT_PRICE");
        String brand = in.getStringExtra("fi.lut.PRODUCT_BRAND");
        db_position = in.getIntExtra("fi.lut.DB_POSITION", -1);

        Bitmap pic = BitmapFactory.decodeByteArray(
                in.getByteArrayExtra("fi.lut.PRODUCT_PICTURE"),
                0,
                in.getByteArrayExtra("fi.lut.PRODUCT_PICTURE").length);

        TextView amountdisp = (TextView) findViewById(R.id.amountTextView);
        TextView namedisp = (TextView) findViewById(R.id.productNameTextView);
        TextView pricedisp = (TextView) findViewById(R.id.priceTextView);
        TextView branddisp = (TextView) findViewById(R.id.brandTextView);
        ImageView picdisp = (ImageView) findViewById(R.id.detailImageView);
        removeItemButton = (Button) findViewById(R.id.removeButton);

        amountdisp.setText(amount);
        namedisp.setText(name);
        pricedisp.setText(price);
        branddisp.setText(brand);

        picdisp.setImageBitmap(pic);

        removeItemButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mRemoveItemFlag = true;

                Intent result = new Intent();
                result.putExtra("fi.lut.REMOVE_FLAG", mRemoveItemFlag);
                result.putExtra("fi.lut.DB_POSITION", db_position);
                setResult(3, result);
                finish();

            }
        });
    }



}
