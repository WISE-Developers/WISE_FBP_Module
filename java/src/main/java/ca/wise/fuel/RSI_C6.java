/***********************************************************************
 * REDapp - RSI_C6.java
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

import ca.hss.general.OutVariable;
import ca.hss.math.HSS_Double;

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.wise.fuel.proto.*;

public class RSI_C6 extends RSI_C1 {
	protected static final long serialVersionUID = 1L;
	
	private double m_fme_multiplier;
	private double m_fme_pow_adder;
	private double m_fme_pow_multiplier;
	private double m_fme_div_adder;
	private double m_fme_div_multiplier;
	private double m_fme_power;
	private double m_rsc_multiplier;
	private double m_rsc_exp_multiplier;
	private double m_fme_avg;
	
	public RSI_C6() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_C6_DEFAULTS, 0.0);
	}

	public RSI_C6(final RSI_C6 other) {
		super(other);
		m_fme_multiplier = other.m_fme_multiplier;
		m_fme_pow_adder = other.m_fme_pow_adder;
		m_fme_pow_multiplier = other.m_fme_pow_multiplier;
		m_fme_div_adder = other.m_fme_div_adder;
		m_fme_div_multiplier = other.m_fme_div_multiplier;
		m_fme_power = other.m_fme_power;
		m_rsc_multiplier = other.m_rsc_multiplier;
		m_rsc_exp_multiplier = other.m_rsc_exp_multiplier;
		m_fme_avg = other.m_fme_avg;
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.ROS_EQ61_MULT1:		return m_fme_multiplier;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_MULT2:		return m_fme_pow_multiplier;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_MULT3:		return m_fme_div_multiplier;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_ADDER1:		return m_fme_pow_adder;	
			case FUELCOM_ATTRIBUTE.ROS_EQ61_ADDER2:		return m_fme_div_adder;	
			case FUELCOM_ATTRIBUTE.ROS_EQ61_POWER:		return m_fme_power;	
			case FUELCOM_ATTRIBUTE.ROS_EQ64_MULT1:		return m_rsc_multiplier;
			case FUELCOM_ATTRIBUTE.ROS_EQ64_MULT2:		return m_rsc_exp_multiplier;
			case FUELCOM_ATTRIBUTE.ROS_EQ64_FMEAVG:		return m_fme_avg;
			case FUELCOM_ATTRIBUTE.RSI_C6_DEFAULTS:
														if ((m_fme_multiplier == 1000.0) &&
															(m_fme_pow_adder == 1.5) &&
															(m_fme_pow_multiplier == 0.00275) &&
															(m_fme_div_adder == 460.0) &&
															(m_fme_div_multiplier == 25.9) &&
															(m_fme_power == 4.0) &&
															(m_rsc_multiplier == 60.0) &&
															(m_rsc_exp_multiplier == 0.0497) &&
															(m_fme_avg == 0.778))					// actual value given on pp37, CFBP system booklet.
															return 1.0;
														return 0.0;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.ROS_EQ61_MULT1:
				m_fme_multiplier = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_MULT2:
				m_fme_pow_multiplier = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_MULT3:
				m_fme_div_multiplier = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_ADDER1:
				m_fme_pow_adder = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_ADDER2:
				m_fme_div_adder = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ61_POWER:
				m_fme_power = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ64_MULT1:
				m_rsc_multiplier = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ64_MULT2:
				m_rsc_exp_multiplier = attribute;
				break;
			case FUELCOM_ATTRIBUTE.ROS_EQ64_FMEAVG:
				if (attribute <= 0.0)
					throw new IllegalArgumentException("One of the inputs is out of range.");
				m_fme_avg = attribute;
				break;
			case FUELCOM_ATTRIBUTE.RSI_C6_DEFAULTS:
				m_fme_multiplier = 1000.0;
				m_fme_pow_adder = 1.5;
				m_fme_pow_multiplier = 0.00275;
				m_fme_div_adder = 460.0;
				m_fme_div_multiplier = 25.9;
				m_fme_power = 4.0;
				m_rsc_multiplier = 60.0;
				m_rsc_exp_multiplier = 0.0497;
				m_fme_avg = 0.778; // actual value given on pp37, CFBP system booklet.
				break;
			default:
				super.setAttributeValue(attributeKey, attribute);
				return;
		}
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_RSI_C6;
	}
	
	@Override
	public double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1) {
		double rsi = super.RSI(sa, flag, ISI, FMC, BUI, FFMC, BE, rsi_c2, rsi_d1);
		rsi_c2.value = rsi;
		rsi_d1.value = rsi;
		return rsi;
	}
	
	@Override
	public double ROS(double RSI, double CBH, double ISI, double FMC, double SFC,
			CFBAttribute cfb) {
		double fme = m_fme_multiplier * Math.pow(m_fme_pow_adder - m_fme_pow_multiplier * FMC, m_fme_power) /
			    (m_fme_div_adder + m_fme_div_multiplier * FMC);		// equation 61

		// cfb should now be calculated, based on this rsi.

		double rsc = m_rsc_multiplier * (1.0 - Math.exp(-m_rsc_exp_multiplier * ISI)) * fme / m_fme_avg;
										// equation 64

		OutVariable<Double> rso; rso = new OutVariable<Double>();
		OutVariable<Double> csi; csi = new OutVariable<Double>();
		
		double ros = RSI + cfb.cfb(CBH, FMC, SFC, RSI, rso, csi) * (rsc - RSI);	// equation 65

		// BE effect was applied inside of the RSI_C1::RSI() call above.
		return ros;
	}

	@Override
	public double FOR_FROS(double RSS, double ROS, double CFB) {
		if (CFB > 0.0)
			return ROS;
		return RSS;
	}	
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof RSI_C6) {
			RSI_C6 a = (RSI_C6)other;
			if (m_fme_multiplier != a.m_fme_multiplier)			return false;
			if (m_fme_pow_adder != a.m_fme_pow_adder)			return false;
			if (m_fme_pow_multiplier != a.m_fme_pow_multiplier)	return false;
			if (m_fme_div_adder != a.m_fme_div_adder)			return false;
			if (m_fme_div_multiplier != a.m_fme_div_multiplier)	return false;
			if (m_fme_power != a.m_fme_power)					return false;
			if (m_rsc_multiplier != a.m_rsc_multiplier)			return false;
			if (m_rsc_exp_multiplier != a.m_rsc_exp_multiplier)	return false;
			if (m_fme_avg != a.m_fme_avg)						return false;
		}
		return super.equals(other);
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.RsiAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.RsiAttribute.Builder builder = ca.wise.fuel.proto.RsiAttribute.newBuilder();
		builder.setVersion((int)RSIAttribute.serialVersionUID);
		
		RsiC6.Builder msgRet = RsiC6.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_C6_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C6);
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_D2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D2);
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_O1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_NZ70_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz70);
			}
		}
	
		if(!serialized) {
			RsiC6.Parms.Builder msg = RsiC6.Parms.newBuilder();

			msg.setVersion(1);
			msg.setFmeMultiplier(HSS_Double.of(m_fme_multiplier));
			msg.setFmePowAdder(HSS_Double.of(m_fme_pow_adder));
			msg.setFmePowMultiplier(HSS_Double.of(m_fme_pow_multiplier));
			msg.setFmeDivAdder(HSS_Double.of(m_fme_div_adder));
			msg.setFmeDivMultiplier(HSS_Double.of(m_fme_div_multiplier));
			msg.setFmePower(HSS_Double.of(m_fme_power));
			msg.setRscMultiplier(HSS_Double.of(m_rsc_multiplier));
			msg.setRscExpMultiplier(HSS_Double.of(m_rsc_exp_multiplier));
			msg.setFmeAvg(HSS_Double.of(m_fme_avg));
			
			msgRet.setParms(msg.build());
		}

		builder.setC6(msgRet);
		return builder.build();
	}

	@Override
	public RSI_C6 deserialize(Message proto) {
		RsiC6 msgRead;
		
		try {
			msgRead = (RsiC6)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			RsiC6.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_fme_multiplier = HSS_Double.from(msg.getFmeMultiplier());
			m_fme_pow_adder = HSS_Double.from(msg.getFmePowAdder());
			m_fme_pow_multiplier = HSS_Double.from(msg.getFmePowMultiplier());
			m_fme_div_adder = HSS_Double.from(msg.getFmeDivAdder());
			m_fme_div_multiplier = HSS_Double.from(msg.getFmeDivMultiplier());
			m_fme_power = HSS_Double.from(msg.getFmePower());
			m_rsc_multiplier = HSS_Double.from(msg.getRscMultiplier());
			m_rsc_exp_multiplier = HSS_Double.from(msg.getRscExpMultiplier());
			m_fme_avg = HSS_Double.from(msg.getFmeAvg());
		}
		else {
			FuelName def = msgRead.getDefault();

			short val = GetDefaultValue(def);

			if(val != (short) -1)
				setAttributeValue(val, 0.0);
			else
				throw new IllegalArgumentException();
		}
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
