-- +AMDG

function donedate(element)
	for key,val in pairs(usedvals) do
		if (val == element) then
			return true
		end
	end
	return false
end

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
	table.insert(usedvals,jdn_easter)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter)),
			TITLE="Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+1)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+1)),
			TITLE="Easter Monday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+2)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+2)),
			TITLE="Easter Tuesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+3)),
			TITLE="Easter Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+4)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+4)),
			TITLE="Easter Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+5)),
			TITLE="Easter Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+6)),
			TITLE="Easter Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,easter",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-2)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-2)),
			TITLE="Good Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-3)),
			TITLE="Holy Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-4)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-4)),
			TITLE="Spy Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-5)),
			TITLE="Tuesday in Holy Week",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-6)),
			TITLE="Monday in Holy Week",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent,holy week",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-46)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-46)),
			TITLE="Ash Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-7)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-7)),
			TITLE="Palm Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-14)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-14)),
			TITLE="Passion Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-21)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-21)),
			TITLE="4th Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-28)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-28)),
			TITLE="3rd Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-35)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-35)),
			TITLE="2nd Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-42)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-42)),
			TITLE="1st Sunday of Lent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="I Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-39)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-39)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="II Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-37)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-37)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="II Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-36)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-36)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",
			CATEGORY="II Class,traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-49)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-49)),
			TITLE="Quinquegesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-56)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-56)),
			TITLE="Sexagesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	table.insert(usedvals,jdn_easter-63)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter-63)),
			TITLE="Septuagesima",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="",CATEGORY="traditional,catholic,lent",
			LOCATION=""
	}
	index = index + 1
	-- Christmas season
	jdn_epiph = greg_to_jdn(year,1,6)
	table.insert(usedvals,jdn_epiph)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_epiph)),
			TITLE="Epiphany",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	index = index + 1
	table.insert(usedvals,jdn_epiph-5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_epiph-5)),
			TITLE="Circumcision of Our Lord",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	circumcision = jdn_epiph-5
	index = index + 1
	table.insert(usedvals,jdn_epiph)
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
	table.insert(usedvals,year,1,2)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(greg_to_jdn(year,1,2))),
				TITLE="Most Holy Name of Jesus",CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,christmas"
		}
	else
	table.insert(usedvals,jdn_epiph-5)
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
	table.insert(usedvals,jdn_christmas)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas)),
			TITLE="Christmas",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,christmas"
	}
	index = index + 1
	-- Advent season
	table.insert(usedvals,jdn_christmas)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas))),
			TITLE="4th Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-7)),
			TITLE="3rd Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,advent"
	}
	third_sun_adv = (last_sunday(jdn_christmas))-7
	index = index + 1
	table.insert(usedvals,third_sun_adv+3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+3)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,third_sun_adv+5)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+5)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,third_sun_adv+6)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(third_sun_adv+6)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-14)),
			TITLE="2nd Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,advent"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(last_sunday(jdn_christmas)-21)),
			TITLE="1st Sunday of Advent",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,advent"
	}
	index = index + 1
	-- Easter Season
	table.insert(usedvals,jdn_easter+7)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+7)),
			TITLE="Low Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+14)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+14)),
			TITLE="2nd Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+21)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+21)),
			TITLE="3rd Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+28)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+28)),
			TITLE="4th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+35)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+35)),
			TITLE="5th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+38)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+38)),
			TITLE="Vigil of the Ascension",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+39)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+39)),
			TITLE="Ascension Thursday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+42)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+42)),
			TITLE="6th Sunday of Easter",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="traditional,catholic,easter"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+49)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+49)),
			TITLE="Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	jdn_pente = jdn_easter+49
	table.insert(usedvals,jdn_easter+50)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+50)),
			TITLE="Monday in the Octave of Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+51)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+51)),
			TITLE="Tuesday in the Octave of Pentecost",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+52)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+52)),
			TITLE="Ember Wednesday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+53)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+53)),
			TITLE="Thursday in the Octave of Pentecost",
			CLASS="Catholic:  1176", START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+54)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+54)),
			TITLE="Ember Friday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+55)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+55)),
			TITLE="Ember Saturday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,pentecost"
	}
	index = index + 1
	table.insert(usedvals,jdn_easter+56)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_easter+56)),
			TITLE="Trinity Sunday",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,pentecost"
	}
	index = index + 1
	-- Make sure Pentecost doesn't overwrite Christ the King
	jdn_ctk = last_sunday(greg_to_jdn(year,11,1))
	modif = 7
	afterpent = 1
	while (jdn_pente+modif < jdn_ctk) do
		table.insert(usedvals,jdn_pente+modif)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(jdn_pente+modif)),
				TITLE=dozenize(afterpent)..last_char(afterpent)..
					" Sunday after Pentecost",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
		afterpent = afterpent + 1
		modif = modif + 7
	end
	table.insert(usedvals,jdn_ctk)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_ctk)),
			TITLE="Christ the King",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="I Class,traditional,catholic,feast"
	}
	index = index + 1
	modif = modif + 7
	afterpent = afterpent + 1
	jdn_first_sunday_advent = last_sunday(jdn_christmas)-21
	while (jdn_pente+modif < jdn_first_sunday_advent) do
		table.insert(usedvals,jdn_pente+modif)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(jdn_pente+modif)),
				TITLE=dozenize(afterpent)..last_char(afterpent)..
					" Sunday after Pentecost",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="II Class,traditional,catholic,feast"
		}
		index = index + 1
		afterpent = afterpent + 1
		modif = modif + 7
	end
	modif = 8
	while ((jdn_christmas-modif < jdn_christmas)) do
		if (dow_from_jdn(jdn_christmas-modif) ~= 0) then
			table.insert(usedvals,jdn_christmas-modif)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(jdn_christmas-modif)),
					TITLE="Feria",
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="II Class,traditional,catholic,feast"
			}
			index = index + 1
		end
		modif = modif - 1
	end
	table.insert(usedvals,jdn_christmas+1)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas+1)),
			TITLE="St. Stephen the Protomartyr, M",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas+2)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas+2)),
			TITLE="St. John the Evangelist, Ap",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	table.insert(usedvals,jdn_christmas+3)
	returntab[index] = {
		START_DATE=print_date(jdn_to_greg(jdn_christmas+3)),
			TITLE="Holy Innocents, M",CLASS="Catholic:  1176",
			START_TIME="",END_TIME="", LOCATION="",
			CATEGORY="II Class,traditional,catholic,feast"
	}
	index = index + 1
	if ((next_sunday(jdn_christmas) < greg_to_jdn(year+1,1,1))
	and (donedate(next_sunday(jdn_christmas)) == false)) then
		table.insert(usedvals,jdn_christmas)
		returntab[index] = {
			START_DATE=print_date(jdn_to_greg(next_sunday(jdn_christmas))),
				TITLE="Sunday within the Octave of Christmas",
				CLASS="Catholic:  1176",
				START_TIME="",END_TIME="", LOCATION="",
				CATEGORY="traditional,catholic,christmas"
		}
		index = index + 1
	end
	modif = 0
	while ((jdn_christmas+modif < greg_to_jdn(year+1,1,1))) do
		if (donedate(jdn_christmas+modif) == false) then
			table.insert(usedvals,jdn_christmas+modif)
			returntab[index] = {
				START_DATE=print_date(jdn_to_greg(jdn_christmas+modif)),
					TITLE="Feria",
					CLASS="Catholic:  1176",
					START_TIME="",END_TIME="", LOCATION="",
					CATEGORY="II Class,traditional,catholic,feast"
			}
			index = index + 1
		end
		modif = modif + 1
	end
--	modif = 0
--	while ((jdn_christmas+modif 


	return index
end

usedvals = {}
returntab = {{}}
index = 1

function dozcal_return_ev()
	return unpack(returntab)
end

function dozcal_return_ev_num()
	return fill_year(2016,returntab,index)
end
