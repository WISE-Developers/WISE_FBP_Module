package ca.wise.fuel;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.TestInstance.Lifecycle;

import com.google.protobuf.Message;
import com.google.protobuf.util.JsonFormat;

import ca.wise.serialize.SerializeProtoOptions;

@TestInstance(Lifecycle.PER_CLASS)
class FuelC1 {

	@Test
	void TestJsonSerialize() {
		assertDoesNotThrow(() -> {
			Cwfgm_Fuel_Readonly fuel0;
			try
			{
				fuel0 = (Cwfgm_Fuel_Readonly)Cwfgm_Fuel_C4.class.getDeclaredConstructor().newInstance();
			}
			catch (Exception e)
			{
				fuel0 = new Cwfgm_Fuel_C1();
			}
			Cwfgm_Fuel_C4 fbpFuel = (Cwfgm_Fuel_C4)fuel0;
			SerializeProtoOptions outOptions = new SerializeProtoOptions();
			outOptions.setVerboseOutput(true);
			
			Message msg = fbpFuel.serialize(outOptions);
			assertNotNull(msg, "The object did not serialize correctly");
			
			String json = JsonFormat.printer().print(msg);
			assertTrue(json.length() > 0, "The serialize JSON string is empty");
		});
	}
}
