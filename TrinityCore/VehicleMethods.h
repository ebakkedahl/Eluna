/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef VEHICLEMETHODS_H
#define VEHICLEMETHODS_H

/***
 * Inherits all methods from: none
 */
namespace LuaVehicle
{
    /**
     * Returns true if the [Unit] passenger is on board
     *
     * @param [Unit] passenger
     * @return bool isOnBoard
     */
    int IsOnBoard(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);

        E->Push(passenger->IsOnVehicle(vehicle->GetBase()));
        return 1;
    }

    /**
     * Returns the [Vehicle]'s owner
     *
     * @return [Unit] owner
     */
    int GetOwner(Eluna* E, Vehicle* vehicle)
    {
        E->Push(vehicle->GetBase());
        return 1;
    }

    /**
     * Returns the [Vehicle]'s entry
     *
     * @return uint32 entry
     */
    int GetEntry(Eluna* E, Vehicle* vehicle)
    {
        E->Push(vehicle->GetVehicleInfo()->ID);
        return 1;
    }

    /**
     * Returns the [Vehicle]'s passenger in the specified seat
     *
     * @param int8 seat
     * @return [Unit] passenger
     */
    int GetPassenger(Eluna* E, Vehicle* vehicle)
    {
        int8 seatId = Eluna::CHECKVAL<int8>(E->L, 2);
        E->Push(vehicle->GetPassenger(seatId));
        return 1;
    }

    /**
     * Adds [Unit] passenger to a specified seat in the [Vehicle]
     *
     * @param [Unit] passenger
     * @param int8 seat
     */
    int AddPassenger(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);
        int8 seatId = Eluna::CHECKVAL<int8>(E->L, 3);

#ifndef CATA
        vehicle->AddPassenger(passenger, seatId);
#else
        vehicle->AddVehiclePassenger(passenger, seatId);
#endif
        return 0;
    }

    /**
     * Removes [Unit] passenger from the [Vehicle]
     *
     * @param [Unit] passenger
     */
    int RemovePassenger(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);

        vehicle->RemovePassenger(passenger);
        return 0;
    }
    
    ElunaRegister<Vehicle> VehicleMethods[] =
    {
        // Getters
        { "GetOwner", &LuaVehicle::GetOwner },
        { "GetEntry", &LuaVehicle::GetEntry },
        { "GetPassenger", &LuaVehicle::GetPassenger },

        // Boolean
        { "IsOnBoard", &LuaVehicle::IsOnBoard },

        // Other
        { "AddPassenger", &LuaVehicle::AddPassenger },
        { "RemovePassenger", &LuaVehicle::RemovePassenger },

        { NULL, NULL }
    };
}

#endif // VEHICLEMETHODS_H
