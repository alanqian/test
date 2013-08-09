/**
 * avos recommendation service rpc protocol definition
 */

namespace java com.avos.recommendation.service
namespace cpp rcmd_service

struct RecommendItem {
  1: string id;
  2: double score = 0.0;
  3: string provider;                // format: provider-version, like mlt-0.1
  4: map<string, string> detail;
}

struct CommonRequest {
  1: string requestId;
  2: string userId;
  3: i64 visitId = 0;
  4: i64 timestamp = 1979;
  5: string app = "";
  6: i32 count = 0;
  7: string format = "";
  8: string token = "";
  9: string encode = "";
  10: string version = "";
  11: string prefs = "";
}

struct CommonResponse {
  1: string requestId = "";
  2: string provider = "";
  3: string version = "";
  4: string object = ""; // stack, user, url
  5: i32 errCode = 0;
     // string errMesg;// only for nice look in json
     // i32 count = 0; // only for nice look in json
  6: list<RecommendItem> items;
}

service RecommenderRpc {
  CommonResponse recommend(1: string api, 2: CommonRequest request, 3: map<string, string> argvs)
}

