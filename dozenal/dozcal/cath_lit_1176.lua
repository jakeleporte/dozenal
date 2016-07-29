-- +AMDG

function greg_to_jdn(year,month,day)
	local a = math.floor((14 - month) / 12)
	local y = year + 4800 - a
	local m = month + (12 * a) - 3
	local jdn = day + math.floor(((153 * m) + 2) / 5) + (365 * y) + 
		math.floor(y / 4) - math.floor(y / 100) + 
		math.floor(y / 400) - 32045
	return jdn
end

function jdn_to_greg(jdn)
	local Q = jdn + 0.5
	local Z = math.floor(Q)
	local W = math.floor((Z - 1867216.25) / 36524.25)
	local X = math.floor(W / 4)
	local A = Z + 1 + W - X
	local B = A + 1524
	local C = math.floor((B - 122.1) / 365.25)
	local D = math.floor(365.25 * C)
	local E = math.floor((B - D) / 30.6001)
	local F = math.floor(30.6001 * E)
	dy = B - D - F + (Q - Z)
	mn = E - 1
	if (mn > 12) then
		mn = E - 13
	end
	if ((mn == 1) or (mn == 2)) then
		yr = C - 4715
	else
		yr = C - 4716
	end
	return math.floor(yr), math.floor(mn), math.floor(dy)
end

function dozenize(num)
	local n = math.floor(num)
	local digits = "0123456789XE"
	local t = {}
	repeat
		local d = (n % 12) + 1
		n = math.floor(n / 12)
		table.insert(t,1,digits:sub(d,d))
	until n == 0
	return table.concat(t,"")
end

function last_char(s)
	if (string.sub(dozenize(s),-1,-1) == "1") then
		return "st"
	elseif (string.sub(dozenize(s),-1,-1) == "2") then
		return "nd"
	elseif (string.sub(dozenize(s),-1,-1) == "3") then
		return "rd"
	else
		return "th"
	end
end

function is_leap_y(y)
	if ((y % 4) == 0) then
		if ((y % 100) == 0) then
			if ((y % 400) == 0) then
				return true
			else
				return false
			end
		else
			return true
		end
	else
		return false
	end
end

function easter(y)
	local a = y % 19
	local b = math.floor(y / 100)
	local c = y % 100
	local d = math.floor(b / 4)
	local e = b % 4
	local f = math.floor((b + 8) / 25)
	local g = math.floor((b - f + 1) / 3)
	local h = (19 * a + b - d - g + 15) % 30
	local i = math.floor(c / 4)
	local k = c % 4
	local L = (32 + 2 * e + 2 * i - h - k) % 7
	local m = math.floor((a + 11 * h + 22 * L) / 451)
	eastermonth = math.floor((h + L - 7 * m + 114) / 31)
	easterday = ((h + L - 7 * m + 114) % 31) + 1
--	print("Easter: "..dozenize(y).."-"..dozenize(eastermonth)..
--		"-"..dozenize(easterday))
	return y, eastermonth, easterday
end

function dow_from_jdn(jdn)
	return ((math.floor(jdn)+1) % 7)
end

function next_sunday(jdn)
	local holder = jdn
	if (dow_from_jdn(holder) == 0) then
		holder = holder + 1
	end
	while (dow_from_jdn(holder) ~= 0) do
		holder = holder + 1
	end
	return holder
end

function last_sunday(jdn)
	local holder = jdn
	if (dow_from_jdn(holder) == 0) then
		holder = holder - 1
	end
	while (dow_from_jdn(holder) ~= 0) do
		holder = holder - 1
	end
	return holder
end

function print_date(year,month,day)
	return dozenize(year).."-"..dozenize(month).."-"..dozenize(day)
end

function fill_year(year,returntab,index)
	-- Easter season
	jdn_easter = greg_to_jdn(easter(year))
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter)),
			TITLE="Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-2)),
			TITLE="Good Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-3)),
			TITLE="Holy Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-4)),
			TITLE="Spy Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-46)),
			TITLE="Ash Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-7)),
			TITLE="Palm Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-14)),
			TITLE="Passion Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-21)),
			TITLE="4th Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-28)),
			TITLE="3rd Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-35)),
			TITLE="2nd Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-42)),
			TITLE="1st Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-49)),
			TITLE="Quinquegesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-56)),
			TITLE="Sexagesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-63)),
			TITLE="Septuagesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	-- Christmas season
	jdn_epiph = greg_to_jdn(year,1,6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_epiph)),
			TITLE="Epiphany",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_epiph-5)),
			TITLE="Circumcision of Our Lord",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	circumcision = jdn_epiph-5
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(next_sunday(jdn_epiph))),
			TITLE="Holy Family",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	index = index + 1
	local holder = jdn_epiph;
	--[[ Holy Name:  Sunday between Circ. and Epiph. if there
	is one, Jan 2 if not ]]--
	while ((dow_from_jdn(holder) ~= 0) and (holder ~= (jdn_epiph - 5))) do
		holder = holder - 1;
	end
	if (holder == (jdn_epiph - 5)) then
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,1,2))),
				TITLE="Most Holy Name of Jesus",CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,christmas"
		}
	else
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(next_sunday(jdn_epiph-5))),
				TITLE="Most Holy Name of Jesus",CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,christmas"
		}
	end
	index = index + 1
	-- end of year Christmas season
	jdn_christmas = greg_to_jdn(year,12,25)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas)),
			TITLE="Christmas",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	index = index + 1
	if (next_sunday(jdn_christmas) < greg_to_jdn(year+1,1,1)) then
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(next_sunday(jdn_christmas))),
				TITLE="Sunday within the Octave of Christmas",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,christmas"
		}
		index = index + 1
	end
	-- Advent season
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas))),
			TITLE="4th Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,advent"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-7)),
			TITLE="3rd Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,advent"
	}
	third_sun_adv = (last_sunday(jdn_christmas))-7
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+3)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,advent"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+5)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,advent"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+6)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,advent"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-14)),
			TITLE="2nd Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,advent"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-21)),
			TITLE="1st Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,advent"
	}
	index = index + 1
	-- Easter Season
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+7)),
			TITLE="Low Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+14)),
			TITLE="2nd Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+21)),
			TITLE="3rd Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+28)),
			TITLE="4th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+35)),
			TITLE="5th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+38)),
			TITLE="Vigil of the Ascension",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+39)),
			TITLE="Ascension Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+42)),
			TITLE="6th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+49)),
			TITLE="Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	jdn_pente = jdn_easter+49
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+50)),
			TITLE="Monday in the Octave of Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+51)),
			TITLE="Tuesday in the Octave of Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+52)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+53)),
			TITLE="Thursday in the Octave of Pentecost",
			CLASS="Catholic:  1176", START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+54)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+55)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+56)),
			TITLE="Trinity Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,pentecost"
	}
	index = index + 1
	-- Make sure Pentecost doesn't overwrite Christ the King
	jdn_ctk = last_sunday(greg_to_jdn(year,11,1))
	modif = 7
	afterpent = 1
	while (jdn_pente+modif < jdn_ctk) do
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(jdn_pente+modif)),
				TITLE=dozenize(afterpent)..last_char(afterpent)..
					" Sunday after Pentecost",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,feast"
		}
		index = index + 1
		afterpent = afterpent + 1
		modif = modif + 7
	end
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_ctk)),
			TITLE="Christ the King",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,feast"
	}
	index = index + 1
	modif = modif + 7
	afterpent = afterpent + 1
	jdn_first_sunday_advent = last_sunday(jdn_christmas)-21
	while (jdn_pente+modif < jdn_first_sunday_advent) do
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(jdn_pente+modif)),
				TITLE=dozenize(afterpent)..last_char(afterpent)..
					" Sunday after Pentecost",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,feast"
		}
		index = index + 1
		afterpent = afterpent + 1
		modif = modif + 7
	end


	return index
end

function dozcal_return_ev()
	returntab = {{}}
	index = 1
	index = fill_year(2016,returntab,index)
	return unpack(returntab)
end

numevents = 23

function dozcal_return_ev_num()
	local returntab = {{}}
	local index = 1
	return fill_year(2016,returntab,index)
end
