/***********************************************************************
 * REDapp - FMC_Calc.java
 * Copyright (C) 2015-2019 The REDapp Development Team
 * Homepage: http://redapp.org
 * 
 * REDapp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * REDapp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with REDapp. If not see <http://www.gnu.org/licenses/>. 
 **********************************************************************/

package ca.wise.fuel;

import java.io.*;
import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.wise.fuel.proto.*;

public class FMC_Calc extends FMCAttribute {
	protected static final long serialVersionUID = 1L;
	
	private short m_day0;
	
	public void serialize(ObjectOutputStream out) throws IOException {
		writeObject(out);
	}
	
	private void writeObject(ObjectOutputStream out) throws IOException {
		out.defaultWriteObject();
	}
	
	private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		in.defaultReadObject();
	}	
	
	public FMC_Calc() {
		m_day0 = -1;
	}

	public FMC_Calc(final FMC_Calc other) {
		m_day0 = other.m_day0;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		FMC_Calc other = (FMC_Calc)super.clone();
		return other;
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FMC_DAY0:			return m_day0;
		}

		return super.getAttributeValue(attributeKey);
	}

	@Override
	public void setAttributeValue(short attributeKey, double attribute) throws IllegalArgumentException {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FMC_DAY0:	if (attribute < -1.0) throw new IllegalArgumentException("One of the inputes is out of range.");
												if (attribute > 365.0)	throw new IllegalArgumentException("One of the inputes is out of range.");
												if ((attribute - Math.floor(attribute)) > 1e-5)	throw new IllegalArgumentException("One of the inputes is out of range.");
												m_day0 = (short)attribute;
												return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}

	@Override
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_FMC_CALC;
	}

	@Override
	public double fmc(double lat, double lon, double elev, int day) {
		if (elev < 0.0) {
			if (elev != -99.0)
				elev = 0.0;
		}
		
		double m_fmc_x;

		assert (lat >= Math.toRadians(-90.0));
		assert (lat <= Math.toRadians(90.0));
		assert (lon >= Math.toRadians(-180.0));
		assert (lon <= Math.toRadians(180.0));

		if (lat < 0.0) {
			day += 182;			// basic, simple correction for flipping from the southern hemisphere to the northern one
			if (day > 365)			// because we're dealing with Canada
				day -= 365;
		}
		if (lat < Math.toRadians(42.0))			lat = Math.toRadians(42.0);
		else if (lat > Math.toRadians(83.0))			lat = Math.toRadians(83.0);
		if (lon < Math.toRadians(-141.0))			lon = Math.toRadians(-141.0);
		else if (lon > Math.toRadians(-52.0))			lon = Math.toRadians(-52.0);

		lat = Math.toDegrees(lat);
		lon = Math.toDegrees(lon);

		if (lon < 0.0)
			lon = 0.0 - lon;

		double latn = -1;						// normalized latitude
		short day0;						// julian day of minimum FMC
		if (m_day0 < 0) {
			if (elev < -98.0) {				// if elevation isn't specified...
				latn = 46.0 + 23.4 * Math.exp(-0.0360 * (150.0 - lon));		// equation 1
				day0 = (short)(0.5 + 151.0 * (lat / latn));					// equation 2
			} else {					// otherwise, elev is considered a valid elevation
				latn = 43.0 + 33.7 * Math.exp(-0.0351 * (150.0 - lon));		// equation 3
				day0 = (short)(0.5 + 142.1 * (lat / latn) + 0.0172 * elev);	// equation 4
			}																
		} else	day0 = m_day0;

		short nd = (short)(day - day0);										// number of days, equation 5
		if (nd < 0)			nd *= -1;										// manually do abs

		if (nd < 30)		m_fmc_x = 85.0 + 0.0189 * nd * nd;				// equation 6
		else if (nd < 50)	m_fmc_x = 32.9 + 3.17 * nd - 0.0288 * nd * nd;	// equation 7
		else				m_fmc_x = 120.0;								// equation 8
		
		return m_fmc_x;					// change from %age to actual value
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof FMC_Calc) {
			FMC_Calc c = (FMC_Calc)other;
			return (m_day0 == c.m_day0);
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.FmcAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.FmcAttribute.Builder builder = ca.wise.fuel.proto.FmcAttribute.newBuilder();
		builder.setVersion((int)FMCAttribute.serialVersionUID);
		
		FmcCalc.Builder msgRet = FmcCalc.newBuilder();
		msgRet.setVersion(1);

		FmcCalc.Parms.Builder msg = FmcCalc.Parms.newBuilder();

		msg.setVersion(1);
		msg.setDay0(m_day0);
		
		msgRet.setParms(msg.build());

		builder.setCalc(msgRet);
		return builder.build();
	}

	@Override
	public FMC_Calc deserialize(Message proto) {
		FmcCalc msgRead;
		
		try {
			msgRead = (FmcCalc)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}
		
		FmcCalc.Parms msg = msgRead.getParms();

		if(msg.getVersion() != 1)
			throw new IllegalArgumentException();
		
		m_day0 = (short)msg.getDay0();
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
