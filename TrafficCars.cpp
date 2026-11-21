#include "fh3mod.h"

#include <cstddef>

namespace {
// Use the road version's bucket when available, or the closest stock category.
// Apply the changes while TrafficCars still identifies the affected car IDs.
constexpr char kUnlockTrafficCars[] = R"sql(
WITH traffic_buckets(MediaName, BucketId) AS (
    VALUES
        ('MER_C32AMG_04',                19),
        ('SUB_LegacyB4GT_05',            19),
        ('PG_BUS_14',                    16),
        ('AUD_S4_04',                    19),
        ('FOR_Transit_11',               16),
        ('TOY_YarisS_08',                23),
        ('FOR_Fiesta_09',                23),
        ('MER_A200Turbo_09',             25),
        ('MIN_JohnCooperWorks_Traffic_09', 23),
        ('PG_BoxTruck_14',               16),
        ('BMW_X5M_TRAFFIC_11',           39),
        ('BMW_323Sport_Traffic_00',      19),
        ('MIT_GALANTVR4_TRAFFIC_92',     32),
        ('MAZ_Mazdaspeed3_Traffic_10',   23),
        ('FIA_500AbarthSS_TRAFFIC_10',   23),
        ('FOR_PursuitUte_Traffic_15',    16)
)
INSERT OR IGNORE INTO Data_Car_Buckets (CarId, CarBucket, BucketHero)
SELECT car.Id, mapping.BucketId, 0
FROM TrafficCars AS traffic
JOIN Data_Car AS car ON car.Id = traffic.CarId
JOIN traffic_buckets AS mapping ON mapping.MediaName = car.MediaName
JOIN CarBuckets AS bucket ON bucket.Id = mapping.BucketId;

UPDATE Data_Car
SET NotAvailableInAutoshow = 0
WHERE NotAvailableInAutoshow = 1
  AND Id IN (SELECT CarId FROM TrafficCars);

DELETE FROM TrafficCars;
)sql";
}

FH3MOD_EXPORT int fh3mod_init(const FH3ModApi* api) {
    if (!api || api->api_version < FH3MOD_API_VERSION ||
        api->size < offsetof(FH3ModApi, add_sql) + sizeof(api->add_sql) ||
        !api->register_mod || !api->log || !api->add_sql) {
        return 1;
    }

    FH3ModInfo info{};
    info.size = sizeof(info);
    info.name = "FH3-TrafficCars";
    info.version = MOD_VERSION;
    info.platform_version = "1.4.2";
    info.github_repo = "suderek22/FH3_TrafficCars";
    info.check_updates = 1;
    info.description = "Makes traffic cars eligible for the Autoshow and fills missing car buckets.";

    FH3Mod* mod = api->register_mod(&info);
    if (!mod) {
        return 1;
    }

    api->add_sql(mod, kUnlockTrafficCars);
    api->log(mod, "Registered; queued traffic-car buckets and Autoshow availability changes.");
    return 0;
}
